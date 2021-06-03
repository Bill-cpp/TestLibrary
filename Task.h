/* Copyright (C) 2021 Bill Rubin
 * Contact: rubin@contractor.net
 *
 * This program is licensed under the MIT license, a copy of which
 * has been provided with this program. You can also find the MIT
 * license at https://OpenSource.org/licenses/MIT
 */

#ifndef TASK_H
#define TASK_H

#include "TaskPolicy.h"

template<class Algorithm> class Task;

class AbstractTask {
    public:
        using Size = unsigned long;
        virtual ~AbstractTask() = default;
        virtual void start(const TaskPolicy&) = 0;
        virtual void waitForCompletion() = 0;
        virtual void deleteResult() = 0;

        template<class Algorithm> const Task<Algorithm>* downcast() const
            {return dynamic_cast<const Task<Algorithm>*>(this);}

        Size taskNumber() const noexcept {return taskNumber_;}

    protected:
        AbstractTask(Size taskNumber) noexcept : taskNumber_(taskNumber) {}
        AbstractTask(AbstractTask&&) = default;

    private:
        Size taskNumber_;
};

template<class Algorithm> class Task : public AbstractTask {
    public:
        using ResultPtr = typename Algorithm::ResultPtr;

        Task(const Algorithm& algorithm, Size taskNumber = 0) : AbstractTask(taskNumber), algorithm_(algorithm) {}
        Task(Task&&) = default;
        virtual void start(const TaskPolicy& taskPolicy) override
            {future_ = std::async(taskPolicy.launchPolicy(), algorithm_, taskPolicy);}
        virtual void waitForCompletion() override {result_ = future_.get();}
        virtual void deleteResult() override {result_.reset();}

        const Algorithm& algorithm() const noexcept {return algorithm_;}
        const ResultPtr& result() const noexcept {return result_;}

    private:
        Algorithm              algorithm_;
        std::future<ResultPtr> future_;
        ResultPtr              result_;
};

template<class Algorithm> class ConstTask {
    public:
        using Size = AbstractTask::Size;
        using ResultPtr = typename Algorithm::ResultPtr;

        ConstTask(const Task<Algorithm>* taskPtr) noexcept : constTask_(
            taskPtr->algorithm(),
            taskPtr->taskNumber(),
            taskPtr->result() ) {}

        const Algorithm& algorithm()  const noexcept {return std::get<0>(constTask_);}
        Size             taskNumber() const noexcept {return std::get<1>(constTask_);}
        const ResultPtr& result()     const noexcept {return std::get<2>(constTask_);}

    private:
        std::tuple<const Algorithm&, Size, const ResultPtr&> constTask_;
};

#endif
