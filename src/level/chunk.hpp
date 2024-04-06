#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "../render/mesh.hpp"

#include "../tile/tile.hpp"

#include "../common/open_simplex_noise.hpp"

#define CHUNK_SIZE_XZ 32
#define CHUNK_SIZE_Y 312

namespace level {

struct Chunk {
    // a 3d pointer to store the tiles that the chunk is made up of
    Tile ***tiles;

    // the mesh containing all solid geometry present in the chunk
    rac::Mesh solid_mesh;

    // x position of the chunk
    i64 x;

    // z position of the chunk
    i64 y;

    // fills the tiles triple pointer with air tiles and also sets the X and Y
    // position of the chunk
    Chunk();

    // generates the chunk using a noise algorithm
    void generate();

    // constructs the chunks mesh from the tile data
    void mesh();

    // renders the chunk with OpenGL
    void render() const;

    // compresses a vertex into a packed u32 format where the relative X  and Z
    // chunk coordinates are packed along with texture information and lighting
    // into a single u32
    constexpr u32 compress_vertex(u8, u8, u16, u8, u8) const;

    // returns an 8 bit value which defines whether or not the specific block
    // location is surrounded by transparent blocks
    u8 adjacency_test(i32, i32, i32);

    // returns the tile ID of the tile at the specified position within the
    // chunk. Returns an air tile if the X, Y or Z coordinate is out of bounds
    TileID tile_id(i32, i32, i32);

    // utility functions to add cube quad faces
    void add_cube_top(u32, u32, u32, u32, u8);
    void add_cube_bottom(u32, u32, u32, u32, u8);
    void add_cube_left(u32, u32, u32, u32, u8);
    void add_cube_right(u32, u32, u32, u32, u8);
    void add_cube_back(u32, u32, u32, u32, u8);
    void add_cube_front(u32, u32, u32, u32, u8);

    // deletes all data allocated by the chunk object, involving the
    // destruction of all tiles in the tiles array
    void destroy();
};

}
