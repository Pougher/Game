#pragma once

#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

#include "../common/types.hpp"

#include "../gfx/shadowmap.hpp"

#include "chunk.hpp"
#include "generator.hpp"
#include "generator_pass.hpp"

namespace level {

struct Level {
    // responsible for providing generation to the chunks
    Generator level_generator;

    // shadowmap to render world shadows with
    gfx::Shadowmap shadowmap;

    // a 2D array of the currently loaded chunk pointers
    Chunk ***loaded_chunks;

    // top left corner chunk coordinates
    i64 corner_x;
    i64 corner_y;

    // the squared view distance of the player (must be an odd number)
    u32 view_distance;

    // constructor to set the view distance and the level generator
    Level(u32, const std::vector<GeneratorPass*>&);

    // constructor that just sets the view distance
    Level(u32);

    // default constructor that does nothing
    Level();

    // initializes the level struct if a constructor has not been called
    void init(u32);

    // initializes the chunk array to empty chunks with their x and y parameters
    // filled
    void init_chunks();

    // gets a level's tile ID from its chunk coordinates and its local tile
    // coordinates
    TileID get_level_tile_id(i64, i64, u32, u32, u32);

    // generates the chunks (called once when the world is initially
    // instantiated)
    void generate();

    // meshes the generated chunks
    void mesh();

    // renders the entire world to OpenGL
    void render();

    // moves the level to a new position, frees all chunks that don't need to
    // be loaded, preserves chunks that remain loaded
    void move(i64, i64);

    // gets the chunks on the edge of the world
    std::vector<Chunk*> get_edge_chunks();

    // destroys all data allocated by the world
    void destroy();
};

}
