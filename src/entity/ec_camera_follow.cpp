#include "ec_camera_follow.hpp"
#include "entity.hpp"
#include "ec_position.hpp"

using namespace entity;

void ECCameraFollow::update(Entity *entity) {
    (void) entity;
    this->camera.update_vectors();
    //entity->get<ECPosition>()->position.x += 0.01f;
}

void ECCameraFollow::tick(Entity *entity) { (void) entity; }
void ECCameraFollow::init(Entity *entity) { (void) entity; }
