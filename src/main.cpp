#include <iostream>

#include "render/window.hpp"
#include "render/mesh.hpp"
#include "render/shader.hpp"
#include "render/array_texture.hpp"
#include "render/grid_atlas.hpp"
#include "level/chunk.hpp"
#include "gfx/camera.hpp"

#include "common/global.hpp"

int main() {
    state = new Global;

    rac::GridAtlas texture(std::string("block_atlas.png"), 16, 16, 16, 16);

    // chunk test
    level::Chunk chunk;
    chunk.mesh();

    state->shaders[0].use();

    state->shaders[0].set_mat4("projection",
        glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f));
    //shader.set_mat4("projection",
    //    glm::ortho(2 * -(1280.0f / 720.0f), 2 * (1280.0f / 720.0f), -2.0f, 2.0f, 0.1f, 100.0f));
    state->shaders[0].set_int("tex", 0);

    // get stuff into isometric view
    glm::mat4 model(1.0f);
    //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //model = glm::rotate(model, glm::radians(145.0f), glm::vec3(.0f, 1.0f, 0.0f));
    state->shaders[0].set_mat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture.array_texture->id);
    glEnable(GL_DEPTH_TEST);

    gfx::Camera *cam =
        &state->player->get<entity::ECCameraFollow>()->camera;

    while (!glfwWindowShouldClose(state->window.window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        state->shaders[0].set_mat4("view", cam->view_matrix());
        chunk.solid_mesh.render();

        state->update();
    }

    state->cleanup();
    texture.destroy();
    chunk.destroy();

    return 0;
}
