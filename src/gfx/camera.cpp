#include "camera.hpp"

using namespace gfx;

Camera::Camera(
    glm::vec3 position,
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
    f32 yaw = -90.0f,
    f32 pitch = 0.0f) {
    // set some variables to do with the camera's state
    this->position = position;
    this->world_up = up;
    this->yaw = yaw;
    this->pitch = pitch;

    // calculate camera vectors
    this->update_vectors();
}

Camera::Camera() {
    // default initialization
    this->position = glm::vec3(0.0f);
    this->world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->yaw = -90.0f;
    this->pitch = 0.0f;

    // calculate camera vectors
    this->update_vectors();
}

glm::mat4 Camera::view_matrix() {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::update_vectors() {
    glm::vec3 front;
    // calculate the new front vector
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(pitch));

    this->front = glm::normalize(front);

    // recalculate the right and up vector
    this->right = glm::normalize(glm::cross(this->front, this->world_up));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
