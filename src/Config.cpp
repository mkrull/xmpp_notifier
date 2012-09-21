/*
 * Config.cpp
 *
 *  Created on: 21.09.2012
 *      Author: mak
 */

#include "Config.h"

using namespace std;

namespace ZabbixNotifier {

    bool Config::load_option(lua_State* L, string option) {
        lua_getglobal(L, option.c_str());

        if (lua_isstring(L, 1)) {
            values[option] = lua_tostring(L, 1);
            lua_pop(L, 1);
        }
        else {
            if (lua_istable(L, 1)) {
                lua_pushnil(L);
                vector<string> vector;
                while (lua_next(L, 1)) {
                    vector.push_back(lua_tostring(L, -1));
                    lua_pop(L, 1);
                }

                values[option] = vector;
            }
            return false;
        }

        return true;
    }

    bool Config::load(string config_file) {

        string valid_options[7] = {
                "user",
                "group",
                "listen",
                "xmpp_username",
                "xmpp_password",
                "xmpp_server",
                "authorized_users"
        };

        lua_State* L = luaL_newstate();

        if (luaL_loadfile(L, config_file.c_str())) {
            return false;
        }

        if (lua_pcall(L, 0, 0, 0)) {
            return false;
        }

        for (int i = 0; i <= 6; i++){
            Config::load_option(L, valid_options[i]);
        }

        lua_close(L);

        return true;
    }

    string Config::get_value(string value){
        return boost::get<string>(values[value]);
    }

    vector<string> Config::get_value_list(string value){
        return boost::get<vector<string> >(values[value]);
    }

    Config::Config(string config_file) {
        if (!Config::load(config_file)){
            throw runtime_error("Could not load config file.");
        }

    }

    Config::~Config() {
    }

} /* namespace ZabbixNotifier */
