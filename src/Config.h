/*
 * Config.h
 *
 *  Created on: 21.09.2012
 *      Author: mak
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <vector>
#include <lua.hpp>
#include <map>
#include <boost/variant.hpp>
#include <stdexcept>

using namespace std;


namespace ZabbixNotifier {

    typedef boost::variant<string, vector<string> > Option;

    class Config {
        private:
            bool load(string config_file);
            bool load_option(lua_State* L, string option);
            map<string, Option> values;
        public:
            Config(string config_file);
            virtual ~Config();
            string get_value(string value);
            vector<string> get_value_list(string value_list);
    };

}

#endif /* CONFIG_H_ */
