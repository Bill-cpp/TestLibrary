#ifndef TEST_H
#define TEST_H

#include "Task.h"
#include <vector>

template<class Algorithm> using ConstTaskVector = std::vector<ConstTask<Algorithm>>;

class Test {
    public:
        using TaskPtr = std::unique_ptr<AbstractTask>;
        using TaskVector = std::vector<TaskPtr>;
        using Size = AbstractTask::Size;
        template<class Algorithm> using TaskPtrVector = std::vector<const Task<Algorithm>*>;

        enum State {unfilled, filled, ran};
        static Size hardwareConcurrency() noexcept {return hardware_concurrency_;}

        Test(Size numSlots = hardwareConcurrency());
        State state() const noexcept {return state_;}
        Size numTasks() const noexcept {return taskVector_.size();}
        Size numSlots() const noexcept {return numSlots_;}
        Size numEmptySlots() const noexcept {return numSlots_ - taskVector_.size();}
        bool incrementNumSlots(Size increment = 1) noexcept;

        template<class Algorithm> bool add(const Algorithm& algorithm, Size numTasks = 1) {
            if(numTasks==0 || numTasks > numEmptySlots()) return true;
            const Size firstEmptyTask = taskVector_.size();
            for(Size i = firstEmptyTask; i<firstEmptyTask + numTasks; ++i) {
                taskVector_.emplace_back(std::make_unique<Task<Algorithm>>(algorithm, i));
                }
            if(numEmptySlots()==0) state_ = filled;
            return false;
            }

        template<class Algorithm> bool fill(const Algorithm& algorithm)
            {return add(algorithm, numEmptySlots());}

        bool run(bool separateThreads = true);

        template<class Algorithm> const ConstTaskVector<Algorithm> tasks() const noexcept {
            ConstTaskVector<Algorithm> constTaskVector;
            constTaskVector.reserve(taskVector_.size());
            for(auto& task : taskVector_) {
                const auto taskPtr = task->downcast<Algorithm>();
                if(taskPtr) constTaskVector.push_back(ConstTask<Algorithm>(taskPtr));
                }
            return constTaskVector;
            }

    private:
        static const Size hardware_concurrency_;

        State      state_;
        Size       numSlots_;
        TaskVector taskVector_;
};

#endif
