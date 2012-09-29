/*
 * Task.h
 *
 *  Created on: Sep 29, 2012
 *      Author: mak
 */

#ifndef TASK_H_
#define TASK_H_

#include <boost/shared_ptr.hpp>
#include "XMPPClient.h"
#include "Config.h"
#include "Logger.h"

using namespace std;
using namespace boost;

namespace Notifier {

    class Task {
        private:
            boost::shared_ptr<XMPPClient> client;
            boost::shared_ptr<Config> config;
            boost::shared_ptr<Logger> logger;
            string action;
            int interval;
        public:
            Task(
                    string action,
                    int interval,
                    boost::shared_ptr<XMPPClient> xmpp_client,
                    boost::shared_ptr<Config> config,
                    boost::shared_ptr<Logger> logger
            ) : action(action),
                interval(interval),
                client(xmpp_client),
                config(config),
                logger(logger)
            {};

            void run_task();
            virtual ~Task();
    };

}

#endif /* TASK_H_ */
