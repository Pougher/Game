#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <utility>
#include <string>

#include "../common/types.hpp"
#include "../common/log.hpp"

namespace rac {

struct Texture {
    // list of texture parameters that are used in texture creation
    std::vector<std::pair<GLenum, GLenum>> texture_parameters;

    // the width and height of the texture (dimensions)
    i32 width, height;

    // the number of channels that the texture has
    i32 channels;

    // the OpenGL ID of the texture
    u32 id;

    // default format is GL_RGBA
    GLenum format;

    // tells OpenGL what internal format to use for the texture. Default value
    // is GL_UNSIGNED_BYTE
    GLenum internal_format = GL_UNSIGNED_BYTE;

    // informs OpenGL if the texture being created has any data attached to it.
    // If this value is true, then the provided data will be used to instantiate
    // the texture. Otherwise, NULL is used
    bool has_data = true;

    // loads an image at the filepath specified in the std::string and
    // generates a texture from it
    Texture(const std::string&);

    // generates an empty texture from a set width and height, setting channels
    Texture(i32, i32, i32);

    // generates an empty texture from a set width and height, setting channels
    // and the internal format of the texture
    Texture(i32, i32, i32, GLenum);

    // simple constructor that does nothing
    Texture();

    // creates a texture from a set of data, using the internal width, height
    // and channels values
    void create_texture_from_data(unsigned char*);

    // creates a texture that consists of 0 bytes
    void zero();

    // initializes the default texture parameters
    void initialize_default_parameters();

    // sets the texture parameters, and resets the default parameter list
    void set_parameters(const std::vector<std::pair<GLenum, GLenum>>&);

    // appends the provided vector of texture parameters to the default
    // parameter list
    void set_additional_parameters(
        const std::vector<std::pair<GLenum, GLenum>>&
    );

    // destroys the texture
    void destroy();
};

}
