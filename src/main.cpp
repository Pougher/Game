#include <iostream>

#include "render/window.hpp"
#include "render/mesh.hpp"
#include "render/shader.hpp"
#include "render/array_texture.hpp"
#include "render/grid_atlas.hpp"

int main() {
    rac::Window window("RAC-DEV_0a", 1280, 720);

    // lets test shaders
    rac::Shader shader(
        "shaders/default_vs.glsl",
        "shaders/default_fs.glsl",
        true
    );
    rac::GridAtlas texture(std::string("block_atlas.png"), 16, 16, 16, 16);

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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture.array_texture->id);

    while (!glfwWindowShouldClose(window.window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.update();
    }

    window.cleanup();
    mesh.destroy();
    shader.destroy();

    return 0;
}
