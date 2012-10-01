/*
 * Action.cpp
 *
 *  Created on: 28.09.2012
 *      Author: mak
 */

#include "Action.h"

namespace Notifier {

    string Action::run_lua_script(string lua_file) const {
        string retval = "Failed to run action.";
        lua_State* L = luaL_newstate();

        if (luaL_dofile(L, lua_file.c_str()) == 0){
            lua_getglobal(L, "result");

            if (lua_isstring(L, 1)){
                retval = lua_tostring(L, 1);
            }

            lua_pop(L, 1);
        }

        lua_close(L);

        return retval;
    }
}

