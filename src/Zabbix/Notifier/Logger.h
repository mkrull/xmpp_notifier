/*
 * Logger.h
 *
 *  Created on: 21.09.2012
 *      Author: mak
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <syslog.h>
#include <string>
#include <cstdlib>

#define EMERG   0   /* system is unusable */
#define ALERT   1   /* action must be taken immediately */
#define CRIT    2   /* critical conditions */
#define ERR     3   /* error conditions */
#define WARNING 4   /* warning conditions */
#define NOTICE  5   /* normal but significant condition */
#define INFO    6   /* informational */
#define DEBUG   7   /* debug-level messages */

using namespace std;

namespace Zabbix { namespace Notifier {

    class Logger {
        public:
            static Logger& Instance();
            Logger();

            void emerg(string line);
            void alert(string line);
            void crit(string line);
            void err(string line);
            void warn(string line);
            void notice(string line);
            void info(string line);
            void debug(string line);
            void log(string line, string level);

            bool set_level(string level);
        private:
            void init();
            static void Cleanup();

            static int level;
            static Logger* MInstance;
    };

}
}

#endif /* LOGGER_H_ */
