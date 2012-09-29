/*
 * Config.cpp
 *
 *  Created on: 21.09.2012
 *      Author: mak
 */

#include "Config.h"

using namespace std;

namespace Notifier {

    bool Config::load_option(lua_State* L, string option) {
        bool retval = true;
        logger->debug("Loading config value " + option);

        // laod value
        lua_getglobal(L, option.c_str());

        // check if stack element is convertable into string
        if (lua_isstring(L, 1)) {
            logger->debug(option + " is a string value");

            string value = lua_tostring(L, 1);
            Config::values[option] = value;

            logger->debug("got value " + value + " for " + option);
        }
        else {
            // check if stack value is table
            if (lua_istable(L, 1)) {
                logger->debug(option + " is a table");

                vector<string> vector;

                int table_length = lua_objlen(L,1);

                // read table into vector
                // TODO check if rows are strings
                for (int i = 1; i <= table_length; i++) {
                    lua_pushinteger(L, i);
                    lua_gettable(L, 1);
                    string table_row = lua_tostring(L, -1);

                    logger->debug("Loading table row value " + table_row + " into " + option);

                    vector.push_back(table_row);
                    lua_pop(L, 1);
                }

                Config::values[option] = vector;
            }
            else if (lua_isnil(L, 1)){
                if (defaults.find(option) == defaults.end()){
                    logger->crit(option + " must be defined");
                    retval = false;
                }
                else {
                    values[option] = defaults[option];
                    logger->warn(option + " not defined in config file, using default: " + get_value(option));
                }
            }
        }

        // pop last value to keep stack in clean state
        lua_pop(L, 1);
        return retval;
    }

    bool Config::load(string config_file) {

        vector<string> options = get_valid_options();

        lua_State* L = luaL_newstate();

        if (luaL_dofile(L, config_file.c_str())) {
            return false;
        }

        for (vector<string>::iterator it = options.begin(); it != options.end(); it++){
            if (Config::load_option(L, *it) == false) {
                lua_close(L);
                return false;
            }
        }

        lua_close(L);
        return true;
    }

    vector<string> Config::get_valid_options(){
        vector<string> options = {
                "user"             , "group"                 ,
                "xmpp_username"    , "xmpp_password"         , "xmpp_resource",
                "log_level"        ,
                "authorized_users" , "notify_users"          ,
                "xmpp_server"      , "xmpp_server_port"      ,
                "script_dir"
        };

        return options;
    }

    string Config::get_value(string value) {
        return boost::get<string>(values[value]);
    }

    vector<string> Config::get_value_list(string value) {
        return boost::get<vector<string> >(values[value]);
    }

    void Config::init_logger(){
        boost::shared_ptr<Logger> logger( new Notifier::Logger());

        Config::logger = logger;
    }

    void Config::init(){
        Config::defaults = {
            {"user"                  , "xmpp_notifier"},
            {"group"                 , "xmpp_notifier"},
            {"log_level"             , "INFO"           },
            {"xmpp_server"           , "localhost"      },
            {"xmpp_server_port"      , "5223"           },
            {"xmpp_resource"         , "bot_at_work"    },
            {"authorized_users"      , vector<string>() },
            {"notify_users"          , vector<string>() },
            {"script_dir"            , "scripts"        },
        };
    }

    Config::Config(boost::shared_ptr<Logger> logger, string config_file){
        Config::logger = logger;
        Config::logger->set_level(LOGLEVEL);

        init();

        if (Config::load(config_file) == false)
            throw runtime_error("Could not load config file.");

    }

    Config::Config(string config_file){

        Config::init();
        Config::init_logger();
        Config::logger->set_level(LOGLEVEL);

        if (Config::load(config_file) == false)
            throw runtime_error("Could not load config file.");
    }

    Config::~Config(){
    }
}
