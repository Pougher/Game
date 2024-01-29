#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace rac;

Texture::Texture() {}

Texture::Texture(const std::string &filepath) {
    // flip the image so that the image doesn't appear upside down
    stbi_set_flip_vertically_on_load(1);

    // load the image data from the file
    unsigned char *data = stbi_load(
        filepath.c_str(),
        &this->width,
        &this->height,
        &this->channels,
        0
    );

    if (data == NULL) {
        rlog::error("Issue loading image: '" + filepath + "'");
        return;
    }

    // finally, create the texture from the data
    this->create_texture_from_data(data);

    // clean up leftover data
    stbi_image_free(data);

#ifndef NDEBUG
    rlog::info("Loaded texture from image '" + filepath + "'");
#endif
}

Texture::Texture(i32 w, i32 h) {
    // create an empty data array that is completely black
    unsigned char data[w * h * 4] = { 0 };

    // set up variables for the texture
    this->width = width;
    this->height = height;
    this->channels = 4;

    // create the empty texture
    this->create_texture_from_data(data);
}

void Texture::create_texture_from_data(unsigned char *data) {
    // generate the texture
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    // set the texture attributes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // set the pixel alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // get the GL pixel format for the texture
    GLenum format = this->to_gl_format();

    // now that the texture is bound, we can start to generate it from the
    // loaded image data
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        this->width,
        this->height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );
}

GLenum Texture::to_gl_format() {
    if (this->channels == 3) return GL_RGB;
    return GL_RGBA;
}

void Texture::destroy() {
    glDeleteTextures(1, &this->id);

    // reset variables
    this->width = 0;
    this->height = 0;
    this->channels = 0;
}
