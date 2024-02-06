#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "../render/mesh.hpp"

#include "../tile/tile.hpp"

#define CHUNK_SIZE_XYZ 16

namespace level {

struct Chunk {
    // a 3d pointer to store the tiles that the chunk is made up of
    Tile ***tiles;

    // the mesh containing all solid geometry present in the chunk
    rac::Mesh solid_mesh;

    // fills the tiles triple pointer with air tiles
    Chunk();

    // constructs the chunks mesh from the tile data
    void mesh();

    // deletes all data allocated by the chunk object, involving the
    // destruction of all tiles in the tiles array
    void destroy();
};

}
