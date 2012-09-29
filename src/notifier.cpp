/*
 * notifier.cpp
 *
 *  Created on: 21.09.2012
 *      Author: mak
 */

#include <iostream>
#include <boost/weak_ptr.hpp>

#include "Notifier/Config.h"
#include "Notifier/Logger.h"
#include "Notifier/XMPPClient.h"
#include "Notifier/Task.h"

using namespace std;
using namespace Notifier;
using namespace boost;


int main(void) {
    boost::shared_ptr<Config> config(new Config("/home/mak/test.lua"));
    boost::shared_ptr<Logger> logger(new Logger());

    boost::shared_ptr<XMPPClient> client(new XMPPClient(config, logger));
    boost::weak_ptr<XMPPClient> client_check(client);

    boost::shared_ptr<XMPPClient> client_ptr;

    thread worker(bind(&XMPPClient::worker, client.get()));

    // TODO replace test with thread group with one tread for each task
    Task* task = new Task("test", 10, client, config, logger);
    thread tasker(bind(&Task::run_task, task));

    while (true) {
        if (client_ptr) {
            logger->debug("XMPP Client exists");
            sleep (10);
        }
        else {
            logger->crit("XMPP Client destroyed");
            worker.join();
            sleep(10);
        }
    }


}
