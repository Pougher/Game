#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "../common/types.hpp"
#include "../common/log.hpp"

namespace rac {

struct Texture {
    // the width and height of the texture (dimensions)
    i32 width, height;

    // the number of channels that the texture has
    i32 channels;

    // the OpenGL ID of the texture
    u32 id;

    // loads an image at the filepath specified in the std::string and
    // generates a texture from it
    Texture(const std::string&);

    // generates an empty texture from a set width and height
    Texture(i32, i32);

    // simple constructor that does nothing
    Texture();

    // creates a texture from a set of data, using the internal width, height
    // and channels values
    void create_texture_from_data(unsigned char*);

    // converts the number of channels to a format OpenGL can understand
    GLenum to_gl_format();

    // destroys the texture
    void destroy();
};

}
