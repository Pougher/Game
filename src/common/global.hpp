#pragma once

#include <string>
#include <cassert>

#include "log.hpp"
#include "timer.hpp"

#include "../render/rac.hpp"
#include "../entity/ec_manager.hpp"
#include "../entity/ec_position.hpp"
#include "../entity/ec_camera_follow.hpp"
#include "../entity/ec_player_controller.hpp"

// manages global state
struct Global {
    // window object
    rac::Window window;

    // entity system manager
    entity::ECManager ec_manager;

    // list of shaders for global use
    std::vector<rac::Shader> shaders;

    // list of textures that are loaded (global)
    std::vector<rac::Texture> textures;

    // the player's entity reference
    entity::Entity *player;

    // responsible for ticking the entity manager every 60 TPS
    Timer ec_manager_tick;

    // initializes all object in the global state
    Global();

    // loads shaders to the global state where every even numbered string is
    // a vertex shader position, and each odd numbered string is a fragment
    // shader position
    void add_shaders(const std::vector<std::string>&);

    // runs update methods on a per frame basis for all components of the
    // global state
    void update();

    // cleans up everything allocated by the global state
    void cleanup();
};

// global state object
extern Global *state;
