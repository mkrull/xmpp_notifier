/*
 * zabbix_notifier.cpp
 *
 *  Created on: 21.09.2012
 *      Author: mak
 */

#include <iostream>
#include <boost/weak_ptr.hpp>

#include "Zabbix/Notifier/Config.h"
#include "Zabbix/Notifier/Logger.h"
#include "Zabbix/Notifier/XMPPClient.h"

using namespace std;
using namespace Zabbix::Notifier;
using namespace boost;


int main(void) {
    boost::shared_ptr<Config> config(new Config("/home/mak/test.lua"));
    boost::shared_ptr<Logger> logger(new Logger());

    boost::shared_ptr<XMPPClient> client(new XMPPClient(config, logger));
    boost::weak_ptr<XMPPClient> client_check(client);

    boost::shared_ptr<XMPPClient> client_ptr;

    thread worker(bind(&XMPPClient::worker, client.get()));

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
