#pragma once

#include "ec_component.hpp"

#include "../gfx/camera.hpp"

namespace entity {

struct ECCameraFollow : ECComponent {
    // camera centered at the player
    gfx::Camera camera;

    void init(Entity*);
    void tick(Entity*);
    void update(Entity*);
};

}
