#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <cassert>

#include "../common/types.hpp"
#include "../common/log.hpp"

#include "texture.hpp"

namespace rac {

struct ArrayTexture : Texture {
    // the width, height and depth of the texture, where its depth represents
    // the number of images in the array texture
    i32 width, height, depth;

    // the number of channels that the texture has
    i32 channels;

    // the OpenGL ID of the texture
    u32 id;

    // generates an array texture from a set of data
    // NOTE: Texture information such as width and height cannot be implicitly
    // determined in an array texture since any N*N image can have a multitude
    // of possible array texture sizes
    ArrayTexture(unsigned char*, i32, i32, i32);

    // creates an array texture from a specified width, height and depth using
    // the specified format, along with the data
    void create_array_texture(i32, i32, i32, GLenum, unsigned char*);

    // destroys the texture
    void destroy();
};

}
