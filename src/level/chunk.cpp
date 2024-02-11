#include "chunk.hpp"
#include "../common/global.hpp"

using namespace level;

Chunk::Chunk() {
    // dynamically allocate the tiles 3d array
    this->tiles = new Tile **[CHUNK_SIZE_XYZ];
    for (i32 x = 0; x < CHUNK_SIZE_XYZ; x++) {
        this->tiles[x] = new Tile *[CHUNK_SIZE_XYZ];
        for (i32 z = 0; z < CHUNK_SIZE_XYZ; z++) {
            this->tiles[x][z] = new Tile[CHUNK_SIZE_XYZ];

            // initialize each tile
            for (i32 i = 0; i < CHUNK_SIZE_XYZ; i++) {
                int random = rand() % 16;
                this->tiles[x][z][i].id = TileID::Air;
                if (random == 1) this->tiles[x][z][i].id = TileID::Grass;
                this->tiles[x][z][i].state = TileState::None;
            }
        }
    }

    // initialize the chunks solid mesh
    // - vertex position attribute
    this->solid_mesh.attribute(rac::Mesh::MeshAttribute {
        .type = GL_FLOAT,
        .length = 3,
        .size = 3 * sizeof(float),
        .index = this->solid_mesh.last()
    });

    // - texture coordinate attribute
    this->solid_mesh.attribute(rac::Mesh::MeshAttribute {
        .type = GL_FLOAT,
        .length = 2,
        .size = 2 * sizeof(float),
        .index = this->solid_mesh.last()
    });
}

void Chunk::mesh() {
    for (float x = 0; x < CHUNK_SIZE_XYZ; x += 1.0f) {
        for (float y = 0; y < CHUNK_SIZE_XYZ; y += 1.0f) {
            for (float z = 0; z < CHUNK_SIZE_XYZ; z += 1.0f) {
                if (this->tile_id(x, y, z) == TileID::Air) continue;
                u8 adjacent = this->adjacency_test(x, y, z);
                if (adjacent & 0x01)
                    this->add_cube_left(x, y, z);
                if (adjacent & 0x02)
                    this->add_cube_right(x, y, z);
                if (adjacent & 0x04)
                    this->add_cube_bottom(x, y, z);
                if (adjacent & 0x08)
                    this->add_cube_top(x, y, z);
                if (adjacent & 0x10)
                    this->add_cube_back(x, y, z);
                if (adjacent & 0x20)
                    this->add_cube_front(x, y, z);
            }
        }
    }

    // construct the mesh
    this->solid_mesh.build();
}

void Chunk::render() const {
    this->solid_mesh.render();
}

constexpr u32 Chunk::compress_vertex(
    u8 x,
    u8 y,
    u8 z,
    u16 texture_id,
    u8 lighting,
    u8 index) const {
    return
        x | y << 5 | z << 10 | texture_id << 15 | lighting << 27 | index << 30;
}

u8 Chunk::adjacency_test(i32 x, i32 y, i32 z) {
    u8 result = 0;

    result |= state->tile_manager.get_transparent(this->tile_id(x - 1, y, z));
    result |=
        state->tile_manager.get_transparent(this->tile_id(x + 1, y, z)) << 1;
    result |=
        state->tile_manager.get_transparent(this->tile_id(x, y - 1, z)) << 2;
    result |=
        state->tile_manager.get_transparent(this->tile_id(x, y + 1, z)) << 3;
    result |=
        state->tile_manager.get_transparent(this->tile_id(x, y, z - 1)) << 4;
    result |=
        state->tile_manager.get_transparent(this->tile_id(x, y, z + 1)) << 5;

    return result;
}

TileID Chunk::tile_id(i32 x, i32 y, i32 z) {
    if (x >= CHUNK_SIZE_XYZ || x < 0
        || y >= CHUNK_SIZE_XYZ || y < 0
        || z >= CHUNK_SIZE_XYZ || z < 0) {
        return TileID::Grass;
    }
    return this->tiles[x][y][z].id;
}

void Chunk::add_cube_bottom(f32 x, f32 y, f32 z) {
    this->solid_mesh.push<float>({
        x, y, z,  0.0f, 1.0f,
        x + 1, y, z,  1.0f, 1.0f,
        x + 1, y, z + 1,  1.0f, 0.0f,
        x + 1, y, z + 1,  1.0f, 0.0f,
        x, y, z + 1,  0.0f, 0.0f,
        x, y, z,  0.0f, 1.0f,
    }, 6);
}

void Chunk::add_cube_top(f32 x, f32 y, f32 z) {
    this->solid_mesh.push<float>({
        x, y + 1, z,  0.0f, 1.0f,
        x + 1, y + 1, z,  1.0f, 1.0f,
        x + 1, y + 1, z + 1,  1.0f, 0.0f,
        x + 1, y + 1, z + 1,  1.0f, 0.0f,
        x, y + 1, z + 1,  0.0f, 0.0f,
        x, y + 1, z,  0.0f, 1.0f
    }, 6);
}

void Chunk::add_cube_back(f32 x, f32 y, f32 z) {
    solid_mesh.push<float>({
        x, y, z,  0.0f, 0.0f,
        x + 1, y, z,  1.0f, 0.0f,
        x + 1, y + 1, z,  1.0f, 1.0f,
        x + 1, y + 1, z,  1.0f, 1.0f,
        x, y + 1, z,  0.0f, 1.0f,
        x, y, z,  0.0f, 0.0f,
    }, 6);
}

void Chunk::add_cube_front(f32 x, f32 y, f32 z) {
    solid_mesh.push<float>({
        x, y, z + 1,  0.0f, 0.0f,
        x + 1, y, z + 1,  1.0f, 0.0f,
        x + 1, y + 1, z + 1,  1.0f, 1.0f,
        x + 1, y + 1, z + 1,  1.0f, 1.0f,
        x, y + 1, z + 1,  0.0f, 1.0f,
        x, y, z + 1,  0.0f, 0.0f,
    }, 6);
}

void Chunk::add_cube_left(f32 x, f32 y, f32 z) {
    solid_mesh.push<float>({
        x, y + 1, z + 1,  1.0f, 1.0f,
        x, y + 1, z,  0.0f, 1.0f,
        x, y, z, 0.0f, 0.0f,
        x, y, z, 0.0f, 0.0f,
        x, y, z + 1,  1.0f, 0.0f,
        x, y + 1, z + 1,  1.0f, 1.0f,
    }, 6);
}

void Chunk::add_cube_right(f32 x, f32 y, f32 z) {
    solid_mesh.push<float>({
        x + 1, y + 1, z + 1,  1.0f, 1.0f,
        x + 1, y + 1, z,  0.0f, 1.0f,
        x + 1, y, z,  0.0f, 0.0f,
        x + 1, y, z,  0.0f, 0.0f,
        x + 1, y, z + 1,  1.0f, 0.0f,
        x + 1, y + 1, z + 1,  1.0f, 1.0f,
    }, 6);
}

void Chunk::destroy() {
    for (i32 i = 0; i < CHUNK_SIZE_XYZ; i++) {
        for (i32 j = 0; j < CHUNK_SIZE_XYZ; j++) {
            delete[] this->tiles[i][j];
        }
        delete[] this->tiles[i];
    }
    delete[] this->tiles;
}
