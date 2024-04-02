#pragma once

#include <glm/glm.hpp>

#include <iostream>

#include "ec_component.hpp"

#include "../level/chunk.hpp"

namespace entity {

struct ECPosition : ECComponent {
    // position of the entity
    glm::vec3 position;

    // the chunk position of the entity
    glm::vec2 chunk_pos;

    void init(Entity*);
    void tick(Entity*);
    void update(Entity*);
};

}
