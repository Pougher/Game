#include <iostream>

#include "render/window.hpp"
#include "render/mesh.hpp"
#include "render/shader.hpp"
#include "render/array_texture.hpp"
#include "render/grid_atlas.hpp"
#include "gfx/camera.hpp"

int main() {
    rac::Window window("RAC-DEV_0a", 1280, 720);

    // lets test shaders
    rac::Shader shader(
        "shaders/default_vs.glsl",
        "shaders/default_fs.glsl",
        true
    );
    rac::GridAtlas texture(std::string("block_atlas.png"), 16, 16, 16, 16);
    gfx::Camera camera;

    rac::Mesh mesh;

    mesh.attribute(
        rac::Mesh::MeshAttribute {
            .type = GL_FLOAT,
            .length = 3,
            .size = 3 * sizeof(float),
            .index = mesh.last()
        }
    );
    mesh.attribute(
        rac::Mesh::MeshAttribute {
            .type = GL_FLOAT,
            .length = 2,
            .size = 2 * sizeof(float),
            .index = mesh.last()
        }
    );

    std::vector<float> vert = {
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top left
        // second triangle
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f // top left
    };

    mesh.push<float>(vert);
    mesh.build();
    shader.use();

    shader.set_mat4("projection",
        glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f));
    shader.set_int("tex", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture.array_texture->id);

    while (!glfwWindowShouldClose(window.window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.set_mat4("view", camera.view_matrix());

        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.position += 0.05f * camera.front;
        }
        if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.position -= 0.05f * camera.front;
        }

        window.update();
    }

    window.cleanup();
    mesh.destroy();
    shader.destroy();
    texture.destroy();

    return 0;
}
