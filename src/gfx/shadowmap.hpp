#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstring>

#include "../render/framebuffer.hpp"
#include "../render/shader.hpp"
#include "../render/texture.hpp"

#include "../common/types.hpp"

namespace gfx {

struct Shadowmap {
    // holds depth values for the world being rendered
    rac::Framebuffer depth_map;

    // pointer to the shadow map shader
    rac::Shader *depth_shader;

    // orthographic projection matrix that transforms coordinates into
    // lightspace coordinates
    glm::mat4 light_projection;

    // the direction in which the light is looking
    glm::mat4 light_view;

    // singular light space transformation matrix
    glm::mat4 light_space_matrix;

    // width and height of the shadowmap
    u32 width;
    u32 height;

    // constructor that default initializes everything using a specified
    // width and height
    Shadowmap(u32, u32);

    // default constructor that does nothing
    Shadowmap();

    // initializes the shadowmap object as a whole
    void init(u32, u32);

    // begins the shadow render pass
    void start_shadow_render();

    // ends the shadow render pass
    void end_shadow_render();

    // destroys all memory allocated
    void destroy();
};

}
