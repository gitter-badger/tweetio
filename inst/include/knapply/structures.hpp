#include "typedefs.hpp"

#include "json.hpp"

namespace knapply { // knapply

class TweetDF {
    vec_chr user_id;
    vec_chr status_id;
    vec_chr created_at;
    vec_chr screen_name;
    vec_chr text;
    vec_chr source;

    vec_chr reply_to_status_id;
    vec_chr reply_to_user_id;
    vec_chr reply_to_screen_name;

    vec_lgl is_quote;
    vec_lgl is_retweeted;

    Rcpp::List hashtags;
    Rcpp::List urls_expanded_url;
    Rcpp::List media_expanded_url;
    Rcpp::List mentions_user_id;
    Rcpp::List mentions_screen_name;
    
    vec_chr lang;

    vec_chr quoted_status_id;
    vec_chr quoted_text;
    vec_chr quoted_created_at;
    vec_chr quoted_source;
    vec_int quoted_favorite_count;
    vec_int quoted_retweet_count;
    vec_chr quoted_user_id;
    vec_chr quoted_screen_name;
    vec_chr quoted_name;
    vec_int quoted_followers_count;
    vec_int quoted_friends_count;
    vec_int quoted_statuses_count;
    vec_chr quoted_location;
    vec_chr quoted_description;
    vec_lgl quoted_verified;

    vec_chr retweet_status_id;
    vec_chr retweet_text;
    vec_chr retweet_created_at;
    vec_chr retweet_source;
    vec_int retweet_favorite_count;
    vec_int retweet_retweet_count;
    vec_chr retweet_user_id;
    vec_chr retweet_screen_name;
    vec_chr retweet_name;
    vec_int retweet_followers_count;
    vec_int retweet_friends_count;
    vec_int retweet_statuses_count;
    vec_chr retweet_location;
    vec_chr retweet_description;
    vec_lgl retweet_verified;

    vec_chr place_url;
    vec_chr place_name;
    vec_chr place_full_name;
    vec_chr place_type;
    vec_chr country;
    vec_chr country_code;
    Rcpp::List bbox_coords;

    vec_chr status_url;
    vec_chr name;
    vec_chr location;
    vec_chr description;
    vec_chr url;
    vec_lgl protected_;                           // `protected` is a C++ reserved keyword
    vec_int followers_count;
    vec_int friends_count;
    vec_int listed_count;
    vec_int statuses_count;
    vec_int favourites_count;
    vec_chr account_created_at;
    vec_lgl verified;
    vec_chr account_lang;
    vec_chr profile_banner_url;
    vec_chr profile_image_url;
    vec_chr timestamp_ms;
    vec_lgl contributors_enabled;

    public:
    TweetDF() {};

    TweetDF(const i64 n_vals) {
        this->user_id                      = vec_chr(n_vals, NA_STRING);
        this->status_id                    = vec_chr(n_vals, NA_STRING);
        this->created_at                   = vec_chr(n_vals, NA_STRING);
        this->screen_name                  = vec_chr(n_vals, NA_STRING);
        this->text                         = vec_chr(n_vals, NA_STRING);
        this->source                       = vec_chr(n_vals, NA_STRING);
        this->reply_to_status_id           = vec_chr(n_vals, NA_STRING);
        this->reply_to_user_id             = vec_chr(n_vals, NA_STRING);
        this->reply_to_screen_name         = vec_chr(n_vals, NA_STRING);
        this->is_quote                     = vec_lgl(n_vals, NA_LOGICAL);
        this->is_retweeted                 = vec_lgl(n_vals, NA_LOGICAL);

        this->hashtags                     = Rcpp::List(n_vals);
        this->urls_expanded_url            = Rcpp::List(n_vals);
        this->media_expanded_url           = Rcpp::List(n_vals);
        this->mentions_user_id             = Rcpp::List(n_vals);
        this->mentions_screen_name         = Rcpp::List(n_vals);

        this->lang                         = vec_chr(n_vals, NA_STRING);

        this->quoted_status_id             = vec_chr(n_vals, NA_STRING); 
        this->quoted_text                  = vec_chr(n_vals, NA_STRING); 
        this->quoted_created_at            = vec_chr(n_vals, NA_STRING); 
        this->quoted_source                = vec_chr(n_vals, NA_STRING); 
        this->quoted_favorite_count        = vec_int(n_vals, NA_INTEGER); 
        this->quoted_retweet_count         = vec_int(n_vals, NA_INTEGER); 
        this->quoted_user_id               = vec_chr(n_vals, NA_STRING); 
        this->quoted_screen_name           = vec_chr(n_vals, NA_STRING); 
        this->quoted_name                  = vec_chr(n_vals, NA_STRING); 
        this->quoted_followers_count       = vec_int(n_vals, NA_INTEGER); 
        this->quoted_friends_count         = vec_int(n_vals, NA_INTEGER); 
        this->quoted_statuses_count        = vec_int(n_vals, NA_INTEGER); 
        this->quoted_location              = vec_chr(n_vals, NA_STRING);
        this->quoted_description           = vec_chr(n_vals, NA_STRING);
        this->quoted_verified              = vec_lgl(n_vals, NA_LOGICAL);

        this->retweet_status_id            = vec_chr(n_vals, NA_STRING);
        this->retweet_text                 = vec_chr(n_vals, NA_STRING);
        this->retweet_created_at           = vec_chr(n_vals, NA_STRING);
        this->retweet_source               = vec_chr(n_vals, NA_STRING);
        this->retweet_favorite_count       = vec_int(n_vals, NA_INTEGER);
        this->retweet_retweet_count        = vec_int(n_vals, NA_INTEGER);
        this->retweet_user_id              = vec_chr(n_vals, NA_STRING);
        this->retweet_screen_name          = vec_chr(n_vals, NA_STRING);
        this->retweet_name                 = vec_chr(n_vals, NA_STRING);
        this->retweet_followers_count      = vec_int(n_vals, NA_INTEGER);
        this->retweet_friends_count        = vec_int(n_vals, NA_INTEGER);
        this->retweet_statuses_count       = vec_int(n_vals, NA_INTEGER);
        this->retweet_location             = vec_chr(n_vals, NA_STRING);
        this->retweet_description          = vec_chr(n_vals, NA_STRING);
        this->retweet_verified             = vec_lgl(n_vals, NA_LOGICAL);

        this->place_url                    = vec_chr(n_vals, NA_STRING);
        this->place_name                   = vec_chr(n_vals, NA_STRING);
        this->place_full_name              = vec_chr(n_vals, NA_STRING);
        this->place_type                   = vec_chr(n_vals, NA_STRING);
        this->country                      = vec_chr(n_vals, NA_STRING);
        this->country_code                 = vec_chr(n_vals, NA_STRING);
        this->bbox_coords                  = Rcpp::List(n_vals, vec_dbl(0));

        // this->status_url                   = vec_chr(n_vals, NA_STRING);
        this->name                         = vec_chr(n_vals, NA_STRING);
        this->location                     = vec_chr(n_vals, NA_STRING);
        this->description                  = vec_chr(n_vals, NA_STRING);
        this->url                          = vec_chr(n_vals, NA_STRING);
        this->protected_                   = vec_lgl(n_vals, NA_LOGICAL);
        this->followers_count              = vec_int(n_vals, NA_INTEGER);
        this->friends_count                = vec_int(n_vals, NA_INTEGER);
        this->listed_count                 = vec_int(n_vals, NA_INTEGER);
        this->statuses_count               = vec_int(n_vals, NA_INTEGER);
        this->favourites_count             = vec_int(n_vals, NA_INTEGER);
        this->account_created_at           = vec_chr(n_vals, NA_STRING);
        this->verified                     = vec_lgl(n_vals, NA_LOGICAL);
        this->account_lang                 = vec_chr(n_vals, NA_STRING);
        this->profile_banner_url           = vec_chr(n_vals, NA_STRING);
        this->profile_image_url            = vec_chr(n_vals, NA_STRING);
        this->timestamp_ms                 = vec_chr(n_vals, NA_STRING);
        this->contributors_enabled         = vec_lgl(n_vals, NA_LOGICAL);

    };

    void push(const rapidjson::Value& x, i64 i) {
        this->user_id[i]                     = get_chr( x["user"]["id_str"] );
        this->status_id[i]                   = get_chr( x["id_str"] );
        this->created_at[i]                  = get_chr( x["created_at"] );
        this->screen_name[i]                 = get_chr( x["user"]["screen_name"] );
        this->text[i]                        = get_chr_check( x["extended_tweet"]["full_text"], x["text"] );
        this->source[i]                      = get_chr( x["source"] );
        this->reply_to_status_id[i]          = get_chr( x["in_reply_to_status_id_str"] );
        this->reply_to_user_id[i]            = get_chr( x["in_reply_to_user_id_str"] );
        this->reply_to_screen_name[i]        = get_chr( x["in_reply_to_screen_name"] );
        this->is_quote[i]                    = get_lgl( x["is_quote_status"] );
        this->is_retweeted[i]                = get_lgl( x["retweeted"] );

        this->hashtags[i]                    = map_entities(x, "hashtags", "text");
        this->urls_expanded_url[i]           = map_entities(x, "urls", "expanded_url");
        this->media_expanded_url[i]          = map_entities(x, "media", "expanded_url");
        this->mentions_user_id[i]            = map_entities(x, "user_mentions", "id_str");
        this->mentions_screen_name[i]        = map_entities(x, "user_mentions", "screen_name");

        this->lang[i]                        = get_chr( x["lang"] );

        this->quoted_status_id[i]            = get_chr( x["quoted_status_id_str"] );
        this->quoted_text[i]                 = get_chr_check( x["quoted_status"]["extended_tweet"]["full_text"], x["quoted_status"]["text"] );
        this->quoted_created_at[i]           = get_chr( x["quoted_status"]["created_at"] );
        this->quoted_source[i]               = get_chr( x["quoted_status"]["source"] );
        this->quoted_favorite_count[i]       = get_int( x["quoted_status"]["favorite_count"] );
        this->quoted_retweet_count[i]        = get_int( x["quoted_status"]["retweet_count"] );
        this->quoted_user_id[i]              = get_chr( x["quoted_status"]["user"]["id_str"] );
        this->quoted_screen_name[i]          = get_chr( x["quoted_status"]["user"]["screen_name"] );
        this->quoted_name[i]                 = get_chr( x["quoted_status"]["user"]["name"] );
        this->quoted_followers_count[i]      = get_int( x["quoted_status"]["user"]["followers_count"] );
        this->quoted_friends_count[i]        = get_int( x["quoted_status"]["user"]["friends_count"] );
        this->quoted_statuses_count[i]       = get_int( x["quoted_status"]["user"]["statuses_count"] );
        this->quoted_location[i]             = get_chr( x["quoted_status"]["user"]["location"] );
        this->quoted_description[i]          = get_chr( x["quoted_status"]["user"]["description"] );
        this->quoted_verified[i]             = get_lgl( x["quoted_status"]["user"]["verified"] );

        this->retweet_status_id[i]           = get_chr( x["retweeted_status"]["id_str"] );
        this->retweet_text[i]                = get_chr_check( x["retweeted_status"]["extended_tweet"]["full_text"], x["retweeted_status"]["text"] );
        this->retweet_created_at[i]          = get_chr( x["retweeted_status"]["created_at"] );
        this->retweet_source[i]              = get_chr( x["retweeted_status"]["source"] );
        this->retweet_favorite_count[i]      = get_int( x["retweeted_status"]["favorite_count"] );
        this->retweet_retweet_count[i]       = get_int( x["retweeted_status"]["retweet_count"] );
        this->retweet_user_id[i]             = get_chr( x["retweeted_status"]["user"]["id_str"] );
        this->retweet_screen_name[i]         = get_chr( x["retweeted_status"]["user"]["screen_name"] );
        this->retweet_name[i]                = get_chr( x["retweeted_status"]["user"]["name"] );
        this->retweet_followers_count[i]     = get_int( x["retweeted_status"]["user"]["followers_count"] );
        this->retweet_friends_count[i]       = get_int( x["retweeted_status"]["user"]["followers_count"] );
        this->retweet_statuses_count[i]      = get_int( x["retweeted_status"]["user"]["statuses_count"] );
        this->retweet_location[i]            = get_chr( x["retweeted_status"]["user"]["location"] );
        this->retweet_description[i]         = get_chr( x["retweeted_status"]["user"]["description"] );
        this->retweet_verified[i]            = get_lgl( x["retweeted_status"]["user"]["verified"] );

        this->place_url[i]                   = get_chr( x["place"]["url"] );
        this->place_name[i]                  = get_chr( x["place"]["name"] );
        this->place_full_name[i]             = get_chr( x["place"]["full_name"] );
        this->place_type[i]                  = get_chr( x["place"]["place_type"] );
        this->country[i]                     = get_chr( x["place"]["country"] );
        this->country_code[i]                = get_chr( x["place"]["country_code"] );
        this->bbox_coords[i]                 = get_bbox( x["place"]["bounding_box"]["coordinates"] );

        // this->status_url                     = get_chr( x[""][""] );
        this->name[i]                        = get_chr( x["user"]["name"] );
        this->location[i]                    = get_chr( x["user"]["location"] );
        this->description[i]                 = get_chr( x["user"]["description"] );
        this->url[i]                         = get_chr( x["user"]["url"] );
        this->protected_[i]                  = get_lgl( x["user"]["protected"] );
        this->followers_count[i]             = get_int( x["user"]["followers_count"] );
        this->friends_count[i]               = get_int( x["user"]["friends_count"] );
        this->listed_count[i]                = get_int( x["user"]["listed_count"] );
        this->statuses_count[i]              = get_int( x["user"]["statuses_count"] );
        this->favourites_count[i]            = get_int( x["user"]["favourites_count"] );
        this->account_created_at[i]          = get_chr( x["user"]["created_at"] );
        this->verified[i]                    = get_lgl( x["user"]["verified"] );
        this->account_lang[i]                = get_chr( x["user"]["lang"] );
        this->profile_banner_url[i]          = get_chr( x["user"]["profile_banner_url"] );
        this->profile_image_url[i]           = get_chr( x["user"]["profile_image_url"] );
        this->timestamp_ms[i]                = get_chr( x["timestamp_ms"] );
        this->contributors_enabled[i]        = get_lgl( x["user"]["countributors_enabled"] );
    };


    Rcpp::List to_r() {
        using Rcpp::_;

        Rcpp::List main = Rcpp::List::create(
            _["user_id"]              = this->user_id,
            _["status_id"]            = this->status_id,
            _["created_at"]           = this->created_at,
            _["screen_name"]          = this->screen_name,
            _["text"]                 = this->text,
            _["source"]               = this->source,
            _["reply_to_status_id"]   = this->reply_to_status_id,
            _["reply_to_user_id"]     = this->reply_to_user_id,
            _["reply_to_screen_name"] = this->reply_to_screen_name,
            _["is_quote"]             = this->is_quote,
            _["is_retweeted"]         = this->is_retweeted
        );
        main.attr("class") = "data.frame";
        main.attr("row.names") = Rcpp::seq( 1, this->user_id.size() );


        Rcpp::List entities = Rcpp::List::create(
            _["hashtags"]             = this->hashtags,
            _["urls_expanded_url"]    = this->urls_expanded_url,
            _["media_expanded_url"]   = this->media_expanded_url,
            _["mentions_user_id"]     = this->mentions_user_id,
            _["mentions_screen_name"] = this->mentions_screen_name
        );
        entities.attr("class") = "data.frame";
        entities.attr("row.names") = Rcpp::seq( 1, this->user_id.size() );


        Rcpp::List meta = Rcpp::List::create(
            _["lang"]                 = this->lang
        );
        meta.attr("class") = "data.frame";
        meta.attr("row.names") = Rcpp::seq( 1, this->user_id.size() );


        Rcpp::List quoted = Rcpp::List::create(
            _["quoted_status_id"]          = this->quoted_status_id,
            _["quoted_text"]               = this->quoted_text,
            _["quoted_created_at"]         = this->quoted_created_at,
            _["quoted_source"]             = this->quoted_source,
            _["quoted_favorite_count"]     = this->quoted_favorite_count,
            _["quoted_retweet_count"]      = this->quoted_retweet_count,
            _["quoted_user_id"]            = this->quoted_user_id,
            _["quoted_screen_name"]        = this->quoted_screen_name,
            _["quoted_name"]               = this->quoted_name,
            _["quoted_followers_count"]    = this->quoted_followers_count,
            _["quoted_friends_count"]      = this->quoted_friends_count,
            _["quoted_statuses_count"]     = this->quoted_statuses_count,
            _["quoted_location"]           = this->quoted_location,
            _["quoted_description"]        = this->quoted_description,
            _["quoted_verified"]           = this->quoted_verified
        );
        quoted.attr("class") = "data.frame";
        quoted.attr("row.names") = Rcpp::seq( 1, this->user_id.size() );


        Rcpp::List retweet = Rcpp::List::create(
            _["retweet_status_id"]         = this->retweet_status_id,
            _["retweet_text"]              = this->retweet_text,
            _["retweet_created_at"]        = this->retweet_created_at,
            _["retweet_source"]            = this->retweet_source,
            _["retweet_favorite_count"]    = this->retweet_favorite_count,
            _["retweet_retweet_count"]     = this->retweet_retweet_count,
            _["retweet_user_id"]           = this->retweet_user_id,
            _["retweet_screen_name"]       = this->retweet_screen_name,
            _["retweet_name"]              = this->retweet_name,
            _["retweet_followers_count"]   = this->retweet_followers_count,
            _["retweet_friends_count"]     = this->retweet_friends_count,
            _["retweet_statuses_count"]    = this->retweet_statuses_count,
            _["retweet_location"]          = this->retweet_location,
            _["retweet_description"]       = this->retweet_description,
            _["retweet_verified"]          = this->retweet_verified
        );
        retweet.attr("class") = "data.frame";
        retweet.attr("row.names") = Rcpp::seq( 1, this->user_id.size() );


        Rcpp::List geo = Rcpp::List::create(
            _["place_url"]                 = this->place_url,
            _["place_name"]                = this->place_name,
            _["place_full_name"]           = this->place_full_name,
            _["place_type"]                = this->place_type,
            _["country"]                   = this->country,
            _["country_code"]              = this->country_code,
            _["bbox_coords"]               = this->bbox_coords
        );
        geo.attr("class") = "data.frame";
        geo.attr("row.names") = Rcpp::seq( 1, this->user_id.size() );

        Rcpp::List other = Rcpp::List::create(
            _["name"]                      = this->name,
            _["location"]                  = this->location,
            _["description"]               = this->description,
            _["url"]                       = this->url,
            _["protected"]                 = this->protected_,
            _["followers_count"]           = this->followers_count,
            _["friends_count"]             = this->friends_count,
            _["listed_count"]              = this->listed_count,
            _["statuses_count"]            = this->statuses_count,
            _["favourites_count"]          = this->favourites_count,
            _["account_created_at"]        = this->account_created_at,
            _["verified"]                  = this->verified,
            _["account_lang"]              = this->account_lang,
            _["profile_banner_url"]        = this->profile_banner_url,
            _["profile_image_url"]         = this->profile_image_url,
            _["timestamp_ms"]              = this->timestamp_ms,
            _["contributors_enabled"]      = this->contributors_enabled
        );
        other.attr("class") = "data.frame";
        other.attr("row.names") = Rcpp::seq( 1, this->user_id.size() );


        return Rcpp::List::create(
            _["main"] = main,
            _["entities"] = entities,
            _["meta"] = meta,
            _["quoted"] = quoted,
            _["retweet"] = retweet,
            _["geo"] = geo,
            _["other"] = other
        );
    };

};


} // knapply