#pragma once

#include "../common/types.hpp"

#include "chunk.hpp"

namespace level {

struct Level {
    // the squared view distance of the player (must be an odd number)
    u32 view_distance;

    // a 2D array of the currently loaded chunks
    Chunk **loaded_chunks;

    // constructor to set the view distance
    Level(u32);

    // generates the chunks (called once when the world is initially
    // instantiated)
    void generate();

    // meshes the generated chunks
    void mesh();

    // renders the entire world to OpenGL
    void render();

    // destroys all data allocated by the world
    void destroy();
};

}
