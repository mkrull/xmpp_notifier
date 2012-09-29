/*
 * Task.cpp
 *
 *  Created on: Sep 29, 2012
 *      Author: mak
 */

#include "Task.h"

namespace Notifier {

//    Task::Task(
//            string action,
//            int interval,
//            shared_ptr<XMPPClient> xmpp_client,
//            shared_ptr<Config> config,
//            shared_ptr<Logger> logger) {}

    void Task::run_task(){
        while (true){
            sleep (interval);
            client->send_action_reply(action);
        }
    }

    Task::~Task() {
    }

}
