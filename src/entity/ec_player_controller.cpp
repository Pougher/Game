#include "ec_player_controller.hpp"
#include "ec_position.hpp"
#include "ec_camera_follow.hpp"
#include "entity.hpp"

#include "../common/global.hpp"

using namespace entity;

void ECPlayerController::tick(Entity *entity) {
    gfx::Camera *cam = &entity->get<ECCameraFollow>()->camera;

    // if the player has moved chunks, move the world
    if (*(this->chunk_pos) != this->old_chunk_pos) {
        this->old_chunk_pos = *(this->chunk_pos);
        //state->world.move(this->old_chunk_pos.x * 32, this->old_chunk_pos.y * 32);
        //state->world.move(state->world.corner_x + 32, state->world.corner_y);
    }

    const float speed = 0.2f;

    if (glfwGetKey(state->window.window, GLFW_KEY_W) == GLFW_PRESS) {
        *cam->position += speed * cam->front;
    }
    if (glfwGetKey(state->window.window, GLFW_KEY_S) == GLFW_PRESS) {
        *cam->position -= speed * cam->front;
    }
    if (glfwGetKey(state->window.window, GLFW_KEY_A) == GLFW_PRESS) {
        *cam->position -=
            glm::normalize(glm::cross(cam->front, cam->up)) * speed;
    }
    if (glfwGetKey(state->window.window, GLFW_KEY_D) == GLFW_PRESS) {
        *cam->position +=
            glm::normalize(glm::cross(cam->front, cam->up)) * speed;
    }
    if (glfwGetKey(state->window.window, GLFW_KEY_SPACE) == GLFW_PRESS)
        (*cam->position)[1] += 1.0f * speed;
    if (glfwGetKey(state->window.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        (*cam->position)[1] -= 1.0f * speed;
}

void ECPlayerController::init(Entity *entity) {
    this->chunk_pos = &entity->get<ECPosition>()->chunk_pos;
}
void ECPlayerController::update(Entity *entity) { (void) entity; }
