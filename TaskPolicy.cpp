/* Copyright (C) 2021 Bill Rubin
 * Contact: rubin@contractor.net
 *
 * This program is licensed under the MIT license, a copy of which
 * has been provided with this program. You can also find the MIT
 * license at https://OpenSource.org/licenses/MIT
 */

#include "TaskPolicy.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const TaskPolicy& taskPolicy) {
    os<<"  Number of tasks: "<<taskPolicy.numTasks()
      <<"\n  Task number: "<<taskPolicy.taskNumber()
      <<"\n  Launch policy: ";
    switch(taskPolicy.launchPolicy()) {
        case std::launch::async:    os<<"async\n";    break;
        case std::launch::deferred: os<<"deferred\n"; break;
        default:                    os<<static_cast<int>(taskPolicy.launchPolicy())<<'\n';
        }
    return os;
}
