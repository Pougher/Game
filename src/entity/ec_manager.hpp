#pragma once

#include <vector>
#include <algorithm>
#include <cstdlib>

#include "entity.hpp"

namespace entity {

struct ECManager {
    // vector containing all available entity IDs (to make ticking and updating
    // more efficient)
    std::vector<size_t> valid_entity_ids;

    // vector containing all of the currently loaded entites
    std::vector<Entity*> entities;

    // free entity slots that can be filled when a new entity is instantiated
    std::vector<size_t> free_slots;

    // just reserves some memory for the entities vector
    ECManager();

    // constructs an entity from the given components and assigns it an ID
    Entity *instantiate_entity(const std::vector<ECComponent*>&);

    // de-allocates the specified entity
    void deallocate(Entity*);

    // ticks all entities in the entity vector
    void tick();

    // calls the frame update methods of all entities in a the vector
    void update();

    // explicitly deletes all heap allocated memory reserved for use in the
    // entity component system
    void cleanup();
};

}
