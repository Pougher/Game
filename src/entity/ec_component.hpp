#pragma once

namespace entity {

// forward declare entity
struct Entity;

struct ECComponent {
    // called to initialize the component to its default values
    virtual void init(Entity*) = 0;

    // tick is called once per in game tick
    virtual void tick(Entity*) = 0;

    // update is called every frame
    virtual void update(Entity*) = 0;

    // default destructor
    virtual ~ECComponent() = default;
};

}
