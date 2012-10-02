/*
 * Action.h
 *
 *  Created on: 28.09.2012
 *      Author: mak
 */

#ifndef ACTION_H_
#define ACTION_H_

#include <map>
#include <string>
#include <lua.hpp>

using namespace std;

namespace Notifier {

    class Action {
        private:
            // for built in actions
            map<string, string (* ) () > dispatch_table;

            // run embedded interpreters
            string run_lua_script ( string lua_file ) const;
            // TODO string run_perl_script(string lua_file) const;

        public:
            // run built in actions
            string operator() ( string name ) const {
                return name;
            }
            string operator() ( string script_dir, string name ) const {
                string lua_file = script_dir + "/lua/" + name;

                // append .lua if not the file suffix
                if ( lua_file.compare ( lua_file.length() - 4, 4, ".lua" ) != 0 )
                    lua_file += ".lua";

                return run_lua_script ( lua_file );
            }
    };

}

#endif /* ACTION_H_ */
