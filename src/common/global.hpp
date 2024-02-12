#pragma once

#include <string>
#include <cassert>

#include "log.hpp"
#include "timer.hpp"

#include "../tile/tile_manager.hpp"

#include "../render/rac.hpp"

#include "../level/level.hpp"

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
    std::unordered_map<std::string, rac::Shader> shaders;

    // map of textures that are used
    std::vector<rac::Texture> textures;

    // the player's entity reference
    entity::Entity *player;

    // responsible for ticking the entity manager every 60 TPS
    Timer ec_manager_tick;

    // stores information about tiles such as their behavior etc.
    TileManager tile_manager;

    // the world that we are rendering
    level::Level world;

    // current fps that the game is operating at
    i32 fps;

    // initializes all object in the global state
    Global();

    // loads shaders to the global state where every even numbered string is
    // a vertex shader position, and each odd numbered string is a fragment
    // shader position
    void add_shaders(
        const std::vector<std::string>&,
        const std::vector<std::string>&
    );

    // runs update methods on a per frame basis for all components of the
    // global state
    void update();

    // cleans up everything allocated by the global state
    void cleanup();
};

// global state object
extern Global *state;
