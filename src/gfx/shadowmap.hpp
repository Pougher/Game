#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstring>

#include "../render/framebuffer.hpp"
#include "../render/texture.hpp"

#include "../common/types.hpp"

struct Shadowmap {
    // holds depth values for the world being rendered
    rac::Framebuffer depth_map;

    // width and height of the shadowmap
    u32 width;
    u32 height;

    // constructor that default initializes everything using a specified
    // width and height
    Shadowmap(u32, u32);
};
