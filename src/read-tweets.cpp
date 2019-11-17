#include <tweetio.hpp>

#include "gzstream.h"

#include <progress.hpp>
#include <progress_bar.hpp>


typedef Rcpp::Vector<STRSXP> vec_chr;
typedef Rcpp::Vector<LGLSXP> vec_lgl;
typedef Rcpp::Vector<INTSXP> vec_int;
typedef Rcpp::Vector<REALSXP> vec_dbl;


enum class TweetFileType: int8_t {
  unknown,
  twitter_api_stream,
  pulse_nested_doc,
  pulse_array
};

int count_lines(const std::string& file_path) {
  igzstream in_file;
  in_file.open( file_path.c_str() );
  
  std::string line_string;
  int out = 0;
  while ( std::getline(in_file, line_string) ) {
    if ( !line_string.empty() ) {
      out++;
    }
  }
  in_file.close();

  return out;
}

TweetFileType detect_file_type(const std::string& file_path) {
  igzstream in_file;
  in_file.open( file_path.c_str() );

  const char first_char = in_file.peek();
  if (first_char == '[') {
    in_file.close();
    return TweetFileType::pulse_array;
  }
  
  std::string line_string;
  rapidjson::Document test_parse;
  rapidjson::ParseResult parse_successful;
  while ( std::getline(in_file, line_string) ) {
    if ( !line_string.empty() ) {
      parse_successful = test_parse.ParseInsitu( (char*)line_string.c_str() );
      if (parse_successful) {
        break;
      }
    }
  }
  in_file.close();

  if ( !parse_successful ) {
    Rcpp::stop("File does not contain any valid JSON.");
  }

  if ( test_parse["id_str"].IsString() || test_parse["delete"]["status"]["id_str"].IsString() ) {
    return TweetFileType::twitter_api_stream;
  }

  if ( test_parse["doc"].IsObject() ) {
    return TweetFileType::pulse_nested_doc;
  }

  return TweetFileType::unknown;
}


template<TweetFileType>
Rcpp::List read_tweets(const std::string&);


template<>
Rcpp::List read_tweets<TweetFileType::pulse_nested_doc>(const std::string& file_path) {
  const int n_lines = count_lines(file_path);
  Progress progress(n_lines, true);

  std::string line_string;
  igzstream in_file;
  in_file.open( file_path.c_str() );

  tweetio::TweetDF tweets(n_lines);
  tweetio::PulseMeta metadata(n_lines);

  
  while ( std::getline(in_file, line_string) ) {
    progress.increment();

    if ( line_string.empty() ) {
      continue;
    }

    rapidjson::Document parsed_json;
    parsed_json.Parse( line_string.c_str() );

    if ( parsed_json["doc"].FindMember("id_str") == parsed_json["doc"].MemberEnd() ) {
      continue;
    }
    
    tweets.push( parsed_json["doc"] );
    metadata.push(parsed_json);
  }

  using Rcpp::_;
  Rcpp::List out = Rcpp::List::create(
    _["tweets"] = tweets.to_r(),
    _["metadata"] = metadata.to_r()
  );  

  out.attr("has_metadata") = true;

  return out;
}


template<>
Rcpp::List read_tweets<TweetFileType::pulse_array>(const std::string& file_path) {
  std::ifstream in_file;
  in_file.open(file_path);

  std::string content;
  in_file.seekg(0, std::ios::end);
  content.resize( in_file.tellg() );
  in_file.seekg(0, std::ios::beg);
  in_file.read( &content[0], content.size() );
  in_file.close();

  rapidjson::Document parsed_json;
  
  rapidjson::ParseResult ok = parsed_json.Parse( content.c_str() );
  if (!ok) {
    Rcpp::stop("parsing error");
  }

  const int n( parsed_json.Size() );
  tweetio::TweetDF tweets(n);
  tweetio::PulseMeta metadata(n);
  Progress progress(n, true);

  for ( const auto& val : parsed_json.GetArray() ) {
    progress.increment();
  
    if ( !val["_source"]["doc"]["id_str"].IsString() ) {
      continue;
    }

    tweets.push(val["_source"]["doc"]);
    metadata.push(val["_source"]);

  }

  using Rcpp::_;
  Rcpp::List out = Rcpp::List::create(
    _["tweets"] = tweets.to_r(),
    _["metadata"] = metadata.to_r()
  );  

  out.attr("has_metadata") = true;

  return out;
}


template<>
Rcpp::List read_tweets<TweetFileType::twitter_api_stream>(const std::string& file_path) {
  std::string line_string;
  std::vector<std::string> raw_json;
  
  igzstream in_file;
  in_file.open( file_path.c_str() );
  while ( std::getline(in_file, line_string) ) {
    if ( !line_string.empty() ) {
      raw_json.push_back(line_string);
    }
  }
  in_file.close();

  tweetio::TweetDF tweets( raw_json.size() );
  tweetio::PulseMeta metadata( raw_json.size() );
  Progress progress(raw_json.size(), true);

  for (const auto& line : raw_json) {
    progress.increment();

    rapidjson::Document parsed_json;
    rapidjson::ParseResult ok = parsed_json.Parse( line.c_str() );
    if (!ok || parsed_json.FindMember("id_str") == parsed_json.MemberEnd() ) {
      continue;
    }
    
    tweets.push(parsed_json);

  }

  using Rcpp::_;
  Rcpp::List out = tweets.to_r();
  out.attr("has_metadata") = false;

  return out;
}


// [[Rcpp::export]]
Rcpp::List read_tweets_impl(const std::string& file_path) {
  const TweetFileType file_type = detect_file_type(file_path);

  switch (file_type) {
    case TweetFileType::pulse_nested_doc:
      return read_tweets<TweetFileType::pulse_nested_doc>(file_path);

    case TweetFileType::pulse_array:
      return read_tweets<TweetFileType::pulse_array>(file_path);
    
    case TweetFileType::twitter_api_stream:
      return read_tweets<TweetFileType::twitter_api_stream>(file_path);
    
    
    case TweetFileType::unknown:
      Rcpp::warning("Unknown data type`.");
      return R_NilValue;
  }

  Rcpp::warning("Unknown data type`.");
  return R_NilValue;
}


/*** R

*/
