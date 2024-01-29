#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "../common/types.hpp"

namespace rac {

struct Window {
    // pointer to the window that we will use
    GLFWwindow *window;

    // the width and height of the window
    u32 width, height;

    // creates the window
    Window(const std::string&, u32, u32);

    // initializes glfw, etc.
    void init();

    // initializes glew
    void init_glew();

    // updates event system, also swaps the window buffer
    void update();

    // cleans up all resources used by the window
    void cleanup();
};

}
