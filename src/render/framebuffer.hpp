#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <optional>

#include "texture.hpp"

#include "../common/types.hpp"

namespace rac {

struct Framebuffer {
    // ID of the framebuffer object itself
    unsigned int id;

    // ID of the renderbuffer object (if there is one)
    std::optional<unsigned int> render_buffer_id;

    // currently bound textures
    std::unordered_map<GLenum, rac::Texture> textures;

    // dimensions of the framebuffer
    u32 width;
    u32 height;

    // constructor which simply sets the dimensions of the framebuffer, and
    // generates a framebuffer object
    Framebuffer(u32, u32);

    // creates a renderbuffer and attaches it to the framebuffer (with the
    // specified format)
    void add_renderbuffer(GLenum, GLenum);

    // attaches a texture to the provided attachment number
    void add_texture(GLenum, const rac::Texture&);

    // binds the framebuffer to the default GL_FRAMEBUFFER
    void bind();

    // destroys all the resources allocated to the framebuffer
    void destroy();
};

}
