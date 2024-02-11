#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <iostream>
#include <cmath>

#include "types.hpp"

struct Timer {
    // the interval in milliseconds that the method is called within
    f64 interval;

    // previous time that the timer was checked for updates
    f64 last_time;

    // the accumulation of timer misses
    f64 accumulation;

    // the method that is called when the appropriate amount of time has passed
    // (only called if update() is called after the interval milliseconds)
    std::function<void()> method;

    // constructor that initializes members
    Timer(f64, const std::function<void()>&);

    // constructor that does nothing
    Timer();

    // updates the timer and calls method if interval amount of milliseconds
    // have passed
    void update();
};
