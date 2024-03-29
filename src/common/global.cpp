#include "global.hpp"

// set state equal to null so we can initialize it later
Global *state = NULL;

Global::Global() : world(8) {
    rlog::info("Instantiated global state object");

    // create the window
    this->window.create("DEV-0g-13_02_2024", 1280, 720);
    rlog::info("Created 1280x720 window");

    // add the default rendering shaders
    this->add_shaders(
        {
            "default",
            "chunk"
        },
        {
            "shaders/default_vs.glsl",
            "shaders/default_fs.glsl",
            "shaders/chunk_vs.glsl",
            "shaders/chunk_fs.glsl"
        }
    );

    // create the player entity
    this->player = this->ec_manager.instantiate_entity({
        new entity::ECPosition,
        new entity::ECCameraFollow,
        new entity::ECPlayerController
    });
    rlog::info("Created player entity");

    // create the 60 TPS entity tick timer
    this->ec_manager_tick.interval = 1.0 / 60.0;
    this->ec_manager_tick.method = []() {
        state->ec_manager.tick();
    };
    rlog::info("Created entity component system tick interval timer");

    rlog::info("Generating world...");
    this->world.level_generator.set_passes({
        new level::TerrainPass
    });
    this->world.generate();

    this->fps = 120;
    rlog::info("Done setting everything up");
}

void Global::add_shaders(
    const std::vector<std::string> &names,
    const std::vector<std::string> &files) {
    // if we loaded an odd number of files then we wouldn't have a pair of
    // fragment and vertex shaders
    assert(files.size() % 2 == 0 && "Number of shaders to load must be"
        && "A multiple of 2");

    // load the shaders
    for (size_t i = 0; i < files.size(); i += 2) {
        this->shaders[
            names[i / 2]] =
            rac::Shader(files[i], files[i + 1], true);
    }
}

void Global::update() {
    // update the window surface
    this->window.update();

    // update the entity component system
    this->ec_manager.update();

    // update the tick timer
    this->ec_manager_tick.update();
}

void Global::cleanup() {
    // destroy the window
    this->window.cleanup();

    // destroy all entities
    this->ec_manager.cleanup();

    // remove data allocated by the loaded level
    this->world.destroy();

    // clean up all of the data allocated to storing tile information
    this->tile_manager.destroy();

    // clean up shaders
    for (auto &[name, shader] : this->shaders) {
        rlog::info("Destroying shader '" + name + "'");
        shader.destroy();
    }
}
