#pragma once

#include <glm/glm.hpp>

#include <iostream>

#include "ec_component.hpp"

namespace entity {

struct ECPosition : ECComponent {
    // position of the entity
    glm::vec3 position;

    void init(Entity*);
    void tick(Entity*);
    void update(Entity*);
};

}
