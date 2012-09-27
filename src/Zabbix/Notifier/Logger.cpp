/*
 * Logger.cpp
 *
 *  Created on: 21.09.2012
 *      Author: mak
 */

#include "Logger.h"
#include <map>

using namespace std;

namespace Zabbix { namespace Notifier {

    void Logger::init(){
        openlog("zabbix-notifier", LOG_PID | LOG_CONS | LOG_NDELAY, LOG_USER);
    }

    bool Logger::set_level(string level){
        map<string, int> level_map;

        level_map["EMERG"]   = EMERG;
        level_map["ALERT"]   = ALERT;
        level_map["CRIT"]    = CRIT;
        level_map["ERR"]     = ERR;
        level_map["WARNING"] = WARNING;
        level_map["NOTICE"]  = NOTICE;
        level_map["INFO"]    = INFO;
        level_map["DEBUG"]   = DEBUG;

        Logger::level = level_map[level];

        return true;
    }

    void Logger::emerg(string line){
        if (Logger::level >= 0)
            syslog(LOG_EMERG, "%s", line.c_str());
    }

    void Logger::alert(string line){
        if (Logger::level >= 1)
            syslog(LOG_ALERT, "%s", line.c_str());
    }

    void Logger::crit(string line){
        if (Logger::level >= 2)
            syslog(LOG_CRIT, "%s", line.c_str());
    }

    void Logger::err(string line){
        if (Logger::level >= 3)
            syslog(LOG_ERR, "%s", line.c_str());
    }

    void Logger::warn(string line){
        if (Logger::level >= 4)
            syslog(LOG_WARNING, "%s", line.c_str());
    }

    void Logger::notice(string line){
        if (Logger::level >= 5)
            syslog(LOG_NOTICE, "%s", line.c_str());
    }

    void Logger::info(string line){
        if (Logger::level >= 6)
            syslog(LOG_INFO, "%s", line.c_str());
    }

    void Logger::debug(string line){
        if (Logger::level >= 7)
            syslog(LOG_DEBUG, "%s", line.c_str());
    }

    // TODO ugly..
    void Logger::log(string line, string level){
        // propably most used first
        if (Logger::level >= 5 && line.compare("NOTICE") == 0){
            notice(line);
        }
        else if (Logger::level >= 6 && line.compare("INFO") == 0){
            info(line);
        }
        else if (Logger::level >= 7 && line.compare("DEBUG") == 0){
            debug(line);
        }
        // hopefuly not used last
        else if (Logger::level >= 4 && line.compare("WARN") == 0){
            warn(line);
        }
        else if (Logger::level >= 3 && line.compare("ERR") == 0){
            err(line);
        }
        else if (Logger::level >= 2 && line.compare("CRIT") == 0){
            crit(line);
        }
        else if (Logger::level >= 1 && line.compare("ALERT") == 0){
            alert(line);
        }
        else if (Logger::level >= 0 && line.compare("EMERG") == 0){
            emerg(line);
        }
    }

    Logger::Logger() {
        init();
    }

    Logger::~Logger(){

    }
}
}
