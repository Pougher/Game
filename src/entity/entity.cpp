#include "entity.hpp"

#include "ec_position.hpp"
#include "ec_camera_follow.hpp"

using namespace entity;

template<typename T> T *Entity::get() {
    for (ECComponent *component : this->components) {
        // check if the component pointer is able to be cast down to the
        // subclass
        if (T *component_ptr = dynamic_cast<T*>(component)) {
            return component_ptr;
        }
    }
    return NULL;
}

template ECPosition *Entity::get();
template ECCameraFollow *Entity::get();
