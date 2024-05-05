#include "shadowmap.hpp"
#include "../common/global.hpp"

using namespace gfx;

Shadowmap::Shadowmap() {}

Shadowmap::Shadowmap(u32 width, u32 height) {
    this->init(width, height);
}

void Shadowmap::init(u32 width, u32 height) {
    this->width = width;
    this->height = height;
    this->depth_map.width = width;
    this->depth_map.height = height;
    this->depth_shader = &state->shaders["gfx_depthmap"];
    this->depth_map.generate();

    // create a texture to attach to the depth map
    rac::Texture texture;

    texture.width = width;
    texture.height = height;
    texture.channels = 1;
    texture.format = GL_DEPTH_COMPONENT;
    texture.internal_format = GL_FLOAT;
    texture.has_data = false;

    texture.set_parameters({
        { GL_TEXTURE_MIN_FILTER, GL_NEAREST },
        { GL_TEXTURE_MAG_FILTER, GL_NEAREST },
        { GL_TEXTURE_WRAP_S, GL_REPEAT },
        { GL_TEXTURE_WRAP_T, GL_REPEAT }
    });

    // instantiate the depth map texture
    texture.zero();

    // attach the depth texture to the depth map
    this->depth_map.add_texture(GL_DEPTH_ATTACHMENT, texture);

    // tell OpenGL not to render any colour data
    this->depth_map.bind();
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // initialize the light space matrix
    const float near_plane = 0.1f;
    const float far_plane = 200.0f;
    this->light_projection = glm::ortho(
        -20.0f, 20.0f,
        -20.0f, 20.0f,
        near_plane,
        far_plane
    );

    this->light_view = glm::lookAt(
        glm::vec3(-2.0f, 100.0f, -1.0f),
        glm::vec3( 0.0f, 0.0f,  0.0f),
        glm::vec3( 0.0f, 1.0f,  0.0f)
    );

    this->light_space_matrix = this->light_view * this->light_projection;
}

void Shadowmap::start_shadow_render() {
    // enable the shadowmap shader first
    this->depth_shader->use();
    this->depth_shader->
        set_mat4("light_space_matrix", this->light_space_matrix);

    // change the viewport to be the width of the shadowmap framebuffer and bind
    // the framebuffer
    glViewport(0, 0, this->width, this->height);
    this->depth_map.bind();

    // clear the depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Shadowmap::end_shadow_render() {
    // reset viewport back to the size of the window.
    // In order to do this, query OpenGL to get the size of the window
    // framebuffer, since some hardware doesn't correctly render the viewport
    // even when given our window width and height as the viewport size (
    // mostly because of scaling)
    int framebuffer_width;
    int framebuffer_height;

    glfwGetFramebufferSize(
        state->window.window,
        &framebuffer_width,
        &framebuffer_height
    );

    // now we can set the viewport size
    glViewport(0, 0, framebuffer_width, framebuffer_height);

    // reset the current rendering framebuffer to the default one
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadowmap::destroy() {
    this->depth_map.destroy();
    this->depth_shader->destroy();
}
