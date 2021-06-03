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
