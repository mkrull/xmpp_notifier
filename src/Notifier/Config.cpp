/*
 * Config.cpp
 *
 *  Created on: 21.09.2012
 *      Author: mak
 */

#include "Config.h"

using namespace std;

namespace Zabbix { namespace Notifier {

    Config* Config::MInstance = 0;

    Config& Config::Instance(string config_file) {
        if (MInstance == 0) {
            MInstance = new Config(config_file);
        }

        return *MInstance;
    }

    Config& Config::Instance() {
        return *MInstance;
    }

    void Config::Cleanup() {
        delete MInstance;
        MInstance = 0;
    }

    bool Config::load_option(lua_State* L, string option) {
        bool retval = true;
        logger.debug("Loading config value " + option);

        // laod value
        lua_getglobal(L, option.c_str());

        // check if stack element is convertable into string
        if (lua_isstring(L, 1)) {
            logger.debug(option + " is a string value");

            string value = lua_tostring(L, 1);
            Config::values[option] = value;

            logger.debug("got value " + value + " for " + option);
        }
        else {
            // check if stack value is table
            if (lua_istable(L, 1)) {
                logger.debug(option + " is a table");

                vector<string> vector;

                int table_length = lua_objlen(L,1);

                // read table into vector
                // TODO check if rows are strings
                for (int i = 1; i <= table_length; i++) {
                    lua_pushinteger(L, i);
                    lua_gettable(L, 1);
                    string table_row = lua_tostring(L, -1);

                    logger.debug("Loading table row value " + table_row + " into " + option);

                    vector.push_back(table_row);
                    lua_pop(L, 1);
                }

                Config::values[option] = vector;
            }
            else if (lua_isnil(L, 1)){
                if (defaults.find(option) == defaults.end()){
                    logger.crit(option + " must be defined");
                    retval = false;
                }
                else {
                    values[option] = defaults[option];
                    logger.warn(option + " not defined in config file, using default: " + get_value(option));
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
        vector<string> options;
        options.push_back("user");
        options.push_back("group");
        options.push_back("listen");
        options.push_back("xmpp_username");
        options.push_back("xmpp_password");
        options.push_back("log_level");
        options.push_back("authorized_users");
        options.push_back("xmpp_server");

        return options;
    }

    string Config::get_value(string value) {
        return boost::get<string>(values[value]);
    }

    vector<string> Config::get_value_list(string value) {
        return boost::get<vector<string> >(values[value]);
    }

    Config::Config(string config_file) {
        Config::logger = Notifier::Logger::Instance();
        Config::logger.set_level(LOGLEVEL);

        Config::defaults["user"] = "zabbix_notifier";
        Config::defaults["group"] = "zabbix_notifier";
        Config::defaults["listen"] = "localhost:4242";
        Config::defaults["log_level"] = "info";
        Config::defaults["xmpp_server"] = "localhost";

        if (Config::load(config_file) == false) {
            throw runtime_error("Could not load config file.");
        }

        atexit(&Cleanup);
    }
}
}