#include "framebuffer.hpp"

using namespace rac;

Framebuffer::Framebuffer() : render_buffer_id(std::nullopt) {}

Framebuffer::Framebuffer(u32 width, u32 height) :
    render_buffer_id(std::nullopt),
    width(width),
    height(height) {
}

void Framebuffer::generate() {
    glGenFramebuffers(1, &this->id);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::add_renderbuffer(GLenum format, GLenum attachment) {
    unsigned int rbo;

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, format, this->width, this->height);

    // attach the renderbuffer to the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        attachment,
        GL_RENDERBUFFER,
        rbo
    );

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // set the optional value to the rbo
    this->render_buffer_id = rbo;
}

void Framebuffer::add_texture(GLenum attachment, const rac::Texture &texture) {
    this->textures[attachment] = texture;

    // attach the texture to the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        attachment,
        GL_TEXTURE_2D,
        texture.id,
        0
    );

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
}

void Framebuffer::destroy() {
    if (this->render_buffer_id.has_value()) {
        unsigned int rbo = this->render_buffer_id.value();
        glDeleteRenderbuffers(1, &rbo);
    }

    for (auto &[key, texture] : this->textures) {
        texture.destroy();
    }

    glDeleteFramebuffers(1, &this->id);
}
