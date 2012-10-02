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

void worker_task ( Task* task ) {
    task->run_task();
}

void worker_client ( boost::shared_ptr<XMPPClient> client ) {
    client->worker();
}

int main ( void ) {

    boost::shared_ptr<Config> config ( new Config ( "/home/mak/test.lua" ) );
    boost::shared_ptr<Logger> logger ( new Logger() );

    logger->set_level ( config->get_value ( "log_level" ) );

    boost::shared_ptr<XMPPClient> client ( new XMPPClient ( config, logger ) );
    boost::weak_ptr<XMPPClient> client_check ( client );

    thread_group tasks;
    map<string, int> tasks_map = config->get_value_map ( "tasks" );

    if ( !tasks_map.empty() ) {
        for ( map<string, int>::iterator i = tasks_map.begin(); i != tasks_map.end(); i++ ) {
            string action = i->first;
            int interval  = i->second;

            logger->notice ( "Creating task " + action );
            Task* task ( new Task ( action, interval, client ) );

            tasks.create_thread ( bind ( &worker_task, task ) );
        }
    }
    else {
        logger->notice ( "No scheduled tasks defined" );
    }

    tasks.create_thread ( bind ( &worker_client, client ) );

    while ( true ) {
        boost::shared_ptr<XMPPClient> client_ptr = client_check.lock();

        if ( client_ptr ) {
            logger->debug ( "XMPP Client object still alive" );
            sleep ( 10 );

        }
        else {
            logger->crit ( "XMPP Client object destroyed" );
            break;
        }
    }

    tasks.join_all();

    delete client.get();
    delete config.get();
    delete logger.get();
}
