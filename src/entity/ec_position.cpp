#include "ec_position.hpp"
#include "entity.hpp"

using namespace entity;

void ECPosition::init(Entity *entity) {
    (void) entity;
    this->position = glm::vec3(0.0f);
}

void ECPosition::tick(Entity *entity) { (void) entity; }
void ECPosition::update(Entity *entity) { (void) entity; }
