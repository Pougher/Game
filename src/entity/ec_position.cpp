#include "ec_position.hpp"
#include "entity.hpp"

using namespace entity;

void ECPosition::init(Entity *entity) {
    (void) entity;
    this->position = glm::vec3(0.0f);
    this->chunk_pos = glm::vec2(0.0f);
}

void ECPosition::update(Entity *entity) {
    (void) entity;
    this->chunk_pos.x = floorf(this->position.x / CHUNK_SIZE_XZ);
    this->chunk_pos.y = floorf(this->position.z / CHUNK_SIZE_XZ);
}

void ECPosition::tick(Entity *entity) { (void) entity; }
