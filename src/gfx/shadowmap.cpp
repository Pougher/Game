#include "shadowmap.hpp"

Shadowmap::Shadowmap(u32 width, u32 height) :
    depth_map(width, height),
    width(width),
    height(height) {
    // create a texture to attach to the depth map
    rac::Texture texture;

    texture.width = width;
    texture.height = height;
    texture.channels = 1;
    texture.format = GL_DEPTH_COMPONENT;

    texture.set_parameters({
        { GL_TEXTURE_MIN_FILTER, GL_NEAREST },
        { GL_TEXTURE_MAG_FILTER, GL_NEAREST },
        { GL_TEXTURE_WRAP_S, GL_REPEAT },
        { GL_TEXTURE_WRAP_T, GL_REPEAT }
    });

    const size_t buffer_size = width * height;
    unsigned char *data = new unsigned char[buffer_size];

    memset(data, 0, buffer_size);

    texture.create_texture_from_data(data);
}
