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
#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <cstdlib>
#include "Logger.h"

#define LOGLEVEL "DEBUG"

using namespace std;

namespace Notifier {

    typedef boost::variant<string, vector<string>, map<string, int> > Option;

    class Config {
        public:
            Config ( string config_file );
            Config ( boost::shared_ptr<Logger> logger, string config_file );
            ~Config();
            string get_value ( string value );
            vector<string> get_value_list ( string value_list );
            map<string, int> get_value_map ( string value );

        private:
            bool load ( string config_file );
            bool load_option ( lua_State* L, string option );

            boost::shared_ptr<Logger> logger;
            map<string, Option> values;
            map<string, Option> defaults;
            void init();
            void init_logger();
            vector<string> get_valid_options();
    };

}

#endif /* CONFIG_H_ */
