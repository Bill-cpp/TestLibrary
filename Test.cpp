#include "Test.h"
#include <exception>

Test::Test(Size numSlots) : state_(unfilled), numSlots_(numSlots) {
    if(numSlots_==0) throw std::invalid_argument("Test constructor argument must be nonzero.");
    taskVector_.reserve(numSlots_);
}

bool Test::incrementNumSlots(Size increment) noexcept {
    if(increment==0) return true;
    if(state_==ran) for(auto& task : taskVector_) task->deleteResult();
    state_ = unfilled;
    numSlots_ += increment;
    taskVector_.reserve(numSlots_);
    return false;
}

bool Test::run(bool separateThreads) {
    if(state_==unfilled) return true;
    const std::launch launchPolicy = separateThreads?std::launch::async:std::launch::deferred;
    for(auto& task : taskVector_) task->start(TaskPolicy(numSlots_, task->taskNumber(), launchPolicy));
    for(auto& task : taskVector_) task->waitForCompletion();
    state_ = ran;
    return false;
}

const Test::Size Test::hardware_concurrency_
    = std::thread::hardware_concurrency()?std::thread::hardware_concurrency():1;
