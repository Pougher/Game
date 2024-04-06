#include <iostream>

#include "render/window.hpp"
#include "render/mesh.hpp"
#include "render/shader.hpp"
#include "render/array_texture.hpp"
#include "render/grid_atlas.hpp"
#include "render/framebuffer.hpp"
#include "level/chunk.hpp"
#include "gfx/camera.hpp"

#include "common/global.hpp"
#include "common/timer.hpp"

// will remove later
int lastX;
int lastY;
bool firstMouse = true;
gfx::Camera *cam;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    (void) window;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam->yaw   += xoffset;
    cam->pitch += yoffset;

    if(cam->pitch > 89.0f)
        cam->pitch = 89.0f;
    if(cam->pitch < -89.0f)
        cam->pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
    direction.y = sin(glm::radians(cam->pitch));
    direction.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
    cam->front = glm::normalize(direction);
}

int main() {
    state = new Global;
    state->world.mesh();

    rac::GridAtlas texture(std::string("atlas.png"), 16, 16, 16, 16);

    // frame per second timer, counts fps
    int fps = 0;
    Timer fps_timer(1.0f, [&fps]() {
        rlog::info("fps = " + std::to_string(fps));
        state->fps = fps;
        fps = 0;
    });
    state->shaders["chunk"].use();

    state->shaders["chunk"].set_mat4("projection",
       glm::perspective(glm::radians(90.0f), 1280.0f / 720.0f, 0.1f, 10000.0f));
    //state->shaders["chunk"].set_mat4("projection",
    //    glm::ortho(8 * -(1280.0f / 720.0f), 8 * (1280.0f / 720.0f), -8.0f,8.0f, 0.1f, 10000.0f));
    state->shaders["chunk"].set_int("tex", 0);

    // get stuff into isometric view
    glm::mat4 model(1.0f);
    //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //model = glm::rotate(model, glm::radians(145.0f), glm::vec3(.0f, 1.0f, 0.0f));
    state->shaders["chunk"].set_mat4("model", model);

    glfwSwapInterval(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture.array_texture->id);
    glEnable(GL_DEPTH_TEST);

    cam = &state->player->get<entity::ECCameraFollow>()->camera;

    glfwSetCursorPosCallback(state->window.window, mouse_callback);
    glfwSetInputMode(state->window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(state->window.window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        state->shaders["chunk"].set_mat4("view", cam->view_matrix());
        state->world.render();

        state->update();

        fps_timer.update();
        fps++;

        if (glfwGetKey(state->window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            break;
    }

    state->cleanup();
    texture.destroy();

    return 0;
}
