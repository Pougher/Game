#pragma once

#include "ec_component.hpp"

namespace entity {

struct ECPlayerController : ECComponent {
    void init(Entity*);
    void tick(Entity*);
    void update(Entity*);
};

};
