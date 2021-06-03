/* Copyright (C) 2021 Bill Rubin
 * Contact: rubin@contractor.net
 *
 * This program is licensed under the MIT license, a copy of which
 * has been provided with this program. You can also find the MIT
 * license at https://OpenSource.org/licenses/MIT
 */

#ifndef TASKPOLICY_H
#define TASKPOLICY_H

#include <future>

class TaskPolicy {
    public:
        using Size = unsigned long;
        TaskPolicy(Size numTasks, Size taskNumber, std::launch launchPolicy) noexcept
            : numTasks_(numTasks), taskNumber_(taskNumber), launchPolicy_(launchPolicy) {}

        Size numTasks() const noexcept {return numTasks_;}
        Size taskNumber() const noexcept {return taskNumber_;}
        std::launch launchPolicy() const noexcept {return launchPolicy_;}

    private:
        Size        numTasks_;
        Size        taskNumber_;
        std::launch launchPolicy_;
};

std::ostream& operator<<(std::ostream&, const TaskPolicy&);

#endif
