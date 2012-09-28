/*
 * Action.h
 *
 *  Created on: 28.09.2012
 *      Author: mak
 */

#ifndef ACTION_H_
#define ACTION_H_

#include <map>

using namespace std;

class Action {
    private:
        map<string, string (*)()> dispatch_table;
        // TODO add lua_script_dir config option
        string run_lua_script(string name);
    public:
        string run(string action);
        Action();
        virtual ~Action();
};

#endif /* ACTION_H_ */
