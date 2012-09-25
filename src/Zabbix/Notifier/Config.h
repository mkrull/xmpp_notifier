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
#include <cstdlib>
#include "Logger.h"

#define LOGLEVEL "INFO"

using namespace std;

namespace Zabbix { namespace Notifier {

    typedef boost::variant<string, vector<string> > Option;

    class Config {
        public:
            static Config& Instance(string config_file);
            static Config& Instance();

            string get_value(string value);
            vector<string> get_value_list(string value_list);

        private:
            Config(string config_file);
            static Config* MInstance;
            static void Cleanup();

            bool load(string config_file);
            bool load_option(lua_State* L, string option);

            Notifier::Logger logger;
            map<string, Option> values;
            map<string, Option> defaults;
            vector<string> get_valid_options();
    };

}
}

#endif /* CONFIG_H_ */
