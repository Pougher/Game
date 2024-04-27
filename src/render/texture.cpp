#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace rac;

Texture::Texture() : format(GL_RGBA) {
    this->initialize_default_parameters();
}

Texture::Texture(const std::string &filepath) :
    format(GL_RGBA) {
    this->initialize_default_parameters();

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

Texture::Texture(i32 w, i32 h, i32 channels) :
    width(w),
    height(h),
    channels(channels) {
    this->initialize_default_parameters();

    // create an empty data array that is completely black
    unsigned char *data = new unsigned char[w * h * this->channels];

    // create the empty texture
    this->create_texture_from_data(data);

    free(data);
}

Texture::Texture(i32 w, i32 h, i32 channels, GLenum format) :
    width(w),
    height(h),
    channels(channels),
    format(format) {
    this->initialize_default_parameters();

    // create an empty data array that is completely black
    const size_t buffer_size = w * h * this->channels;
    unsigned char *data = new unsigned char[buffer_size];

    // memset all data to zero
    memset(data, 0, buffer_size);

    // create the empty texture
    this->create_texture_from_data(data);

    delete[] data;
}

void Texture::create_texture_from_data(unsigned char *data) {
    // generate the texture
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    // set the texture attributes from the texture paramters list
    for (auto &parameter : this->texture_parameters) {
        glTexParameteri(GL_TEXTURE_2D, parameter.first, parameter.second);
    }

    // set the pixel alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // now that the texture is bound, we can start to generate it from the
    // loaded image data
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        this->format,
        this->width,
        this->height,
        0,
        this->format,
        GL_UNSIGNED_BYTE,
        data
    );
}

void Texture::set_parameters(
    const std::vector<std::pair<GLenum, GLenum>> &params) {
    this->texture_parameters.clear();
    this->texture_parameters = params;
}

void Texture::set_additional_parameters(
    const std::vector<std::pair<GLenum, GLenum>> &params) {
    this->texture_parameters.insert(
        this->texture_parameters.end(),
        params.begin(),
        params.end()
    );
}

void Texture::initialize_default_parameters() {
    this->texture_parameters.push_back({ GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE });
    this->texture_parameters.push_back({ GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE });
    this->texture_parameters.push_back({ GL_TEXTURE_MIN_FILTER, GL_NEAREST });
    this->texture_parameters.push_back({ GL_TEXTURE_MAG_FILTER, GL_NEAREST });
}

void Texture::destroy() {
    glDeleteTextures(1, &this->id);

    // reset variables
    this->width = 0;
    this->height = 0;
    this->channels = 0;
}
