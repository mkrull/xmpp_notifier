/*
 ============================================================================
 Name        : zabbix_notifier.cpp
 Author      : Matthias Krull
 Version     :
 Copyright   : All rights reserved.
 Description : Hello World in C++,
 ============================================================================
 */

#include <iostream>


#include "Zabbix/Notifier/Config.h"
#include "Zabbix/Notifier/Logger.h"
#include "Zabbix/Notifier/XMPPClient.h"

using namespace std;
using namespace Zabbix::Notifier;
using namespace boost;


int main(void) {
    boost::shared_ptr<Config> config(new Config("/home/mak/test.lua"));
    boost::shared_ptr<Logger> logger(new Logger());
	XMPPClient* client = new XMPPClient(config, logger);
}
