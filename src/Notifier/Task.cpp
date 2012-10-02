/*
 * Task.cpp
 *
 *  Created on: Sep 29, 2012
 *      Author: mak
 */

#include "Task.h"

namespace Notifier {

    void Task::run_task() {
        while ( true ) {
            sleep ( interval );
            client->send_action_reply ( action );
        }
    }

    Task::~Task() {
    }

}
