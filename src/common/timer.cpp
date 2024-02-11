#include "timer.hpp"

Timer::Timer () {
    this->last_time = glfwGetTime();
}

Timer::Timer(f64 interval, const std::function<void()> &method) :
    interval(interval), method(method) {
    this->last_time = glfwGetTime();
}


void Timer::update() {
    if (glfwGetTime() >= (this->last_time + this->interval)) {
        // accumulate all of the missed updates that may have occured and then
        // once they have accumulated to more than one interval, execute that
        // interval the number of times it has been missed plus one
        f64 diff = glfwGetTime() - this->last_time;
        if (diff > this->interval) {
            this->accumulation += diff - this->interval;
        }
        // calculate the number of intervals that have been missed
        i32 intervals = 1;
        if (this->accumulation >= this->interval) {
            intervals += (i32)floorf(this->accumulation / this->interval);
            this->accumulation = 0.0f;
        }
        // call the function as many times as intervals have missed to
        // synchronise everything
        for (i32 i = 0; i < intervals; i++) {
            this->method();
        }
        this->last_time = glfwGetTime();
    }
}
