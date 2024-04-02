#pragma once

#include <glm/glm.hpp>

#include "ec_component.hpp"

namespace entity {

struct ECPlayerController : ECComponent {
    glm::vec2 old_chunk_pos;
    glm::vec2 *chunk_pos;

    void init(Entity*);
    void tick(Entity*);
    void update(Entity*);
};

};
