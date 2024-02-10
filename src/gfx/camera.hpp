#pragma once

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../common/types.hpp"

namespace gfx {

struct Camera {
    // pointer to the position of the camera in world space
    glm::vec3 *position;

    // front face of the camera
    glm::vec3 front;

    // which way is up
    glm::vec3 up;

    // which way is right
    glm::vec3 right;

    // used to normalize the up coordinate so that we don't move more slowly
    // when the camera is pointed at the ground
    glm::vec3 world_up;

    // euler angles of the camera
    f32 yaw;
    f32 pitch;

    // simple constructor that sets values for the camera
    Camera(glm::vec3*, glm::vec3, f32, f32);

    // constructor that default initializes the vectors of the camera
    Camera();

    // returns the view matrix calculated from the euler angles and the lookat
    // matrix
    glm::mat4 view_matrix();

    // updates the front, right and up vectors of the camera
    void update_vectors();
};

}
