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
        // call the function
        this->method();
        this->last_time = glfwGetTime();
    }
}
