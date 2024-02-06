#pragma once

#include <vector>

#include "ec_component.hpp"

#include "../common/types.hpp"

namespace entity {

struct Entity {
    // ID of the entity
    size_t id;

    // list of entity components that the entity contains
    std::vector<ECComponent*> components;

    // gets a specific type from the entitys component vector
    template<typename T> T *get();
};

}
