#include "array_texture.hpp"
#include "stb_image.h"

using namespace rac;

ArrayTexture::ArrayTexture(
    unsigned char *data,
    i32 width,
    i32 height,
    i32 depth) {
    // check that this GPU supports array textures as large as this
    GLint max_array_layers;
    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &max_array_layers);

    if (max_array_layers < depth) {
        rlog::error(
            std::string(
                "This GPU does not support enough array textures! (needed: ")
            + std::to_string(depth) + ", supports: "
            + std::to_string(max_array_layers));
        return;
    }

    // finally create the array texture
    this->create_array_texture(
        width,
        height,
        depth,
        Texture::to_gl_format(),
        data
    );
}

void ArrayTexture::create_array_texture(
    i32 width,
    i32 height,
    i32 depth,
    GLenum format,
    unsigned char *data) {
    // set variables within the struct
    this->width = width;
    this->height = height;
    this->depth = depth;

    // generate the texture
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->id);

    // set the texture attributes
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // now that all of the parameters have been set up we can start to
    // generate the array texture
    glTexImage3D(
        GL_TEXTURE_2D_ARRAY,
        0,
        GL_RGBA,
        width,
        height,
        depth,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );
}

void ArrayTexture::destroy() {
    glDeleteTextures(1, &this->id);
    this->width = 0;
    this->height = 0;
    this->depth = 0;
}
