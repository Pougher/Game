#include "global.hpp"

// set state equal to null so we can initialize it later
Global *state = NULL;

Global::Global() {
    rlog::info("Instantiated global state object");
}

void Global::init() {
    rlog::info("Initializing global state object...");

    // create the window
    this->window.create("DEV-11h-27_04_2024", 1280, 720);
    rlog::info("Created 1280x720 window");

    // add the default rendering shaders
    this->load_shaders();

    // create the world instance
    rlog::info("Creating LEVEL 0...");
    this->world.init(8);

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
        const std::string &name = names[i / 2];

        // if the shader is already registered, don't register it again
        if (this->shaders.find(name) == this->shaders.end()) {
            this->shaders[name] = rac::Shader(files[i], files[i + 1], true);
        }
    }
}

void Global::load_shaders() {
    try {
        // load the TOML source
        const auto shader_list = toml::parse("shaders/shaders.toml");

        std::vector<std::string> names;
        std::vector<std::string> filenames;

        for (const auto &[key, value] : shader_list.as_table()) {
            const auto &table = toml::find(shader_list, key);

            // load the vertex and fragment shader filenames from the shader
            // table
            const auto &vertex = toml::find<std::string>(table, "vertex");
            const auto &fragment = toml::find<std::string>(table, "fragment");

            names.push_back(key);
            filenames.push_back(vertex);
            filenames.push_back(fragment);
        }

        // finally, load all of the shaders at once
        this->add_shaders(names, filenames);
    } catch (std::exception &e) {
        rlog::error("Error when attempting to load shader configs:");
        std::cerr << "    " << e.what() << std::endl;
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
