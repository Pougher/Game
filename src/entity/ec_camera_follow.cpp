#include "ec_camera_follow.hpp"
#include "entity.hpp"
#include "ec_position.hpp"

using namespace entity;

void ECCameraFollow::init(Entity *entity) {
    // get the position component and set the camera's position to that
    // position
    ECPosition *pos = entity->get<ECPosition>();
    this->camera.position = &pos->position;
}

void ECCameraFollow::update(Entity *entity) {
    (void) entity;
    this->camera.update_vectors();
}

void ECCameraFollow::tick(Entity *entity) { (void) entity; }
