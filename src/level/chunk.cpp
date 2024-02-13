#include "chunk.hpp"

#include "../common/global.hpp"
#include "../common/open_simplex_noise.hpp"

using namespace level;

Chunk::Chunk() {
    // dynamically allocate the tiles 3d array
    this->tiles = new Tile **[CHUNK_SIZE_XZ];
    for (i32 x = 0; x < CHUNK_SIZE_XZ; x++) {
        this->tiles[x] = new Tile *[CHUNK_SIZE_Y];
        for (i32 z = 0; z < CHUNK_SIZE_Y; z++) {
            this->tiles[x][z] = new Tile[CHUNK_SIZE_XZ];

            // initialize each tile
            for (i32 i = 0; i < CHUNK_SIZE_XZ; i++) {
                this->tiles[x][z][i].id = TileID::Air;
                this->tiles[x][z][i].state = TileState::None;
            }
        }
    }

    // initialize the chunks solid mesh
    // vertices are compressed down to 4 bytes
    this->solid_mesh.attribute(rac::Mesh::MeshAttribute {
        .type = GL_UNSIGNED_INT,
        .length = 2,
        .size = 2 * sizeof(u32),
        .index = this->solid_mesh.last()
    });
}

void Chunk::generate() {
    OpenSimplexNoise::Noise noise(69.0f);

    for (u32 x = 0; x < CHUNK_SIZE_XZ; x++) {
        for (u32 z = 0; z < CHUNK_SIZE_XZ; z++) {
            float noise_x = (static_cast<f64>(x + this->x) / 16.0f);
            float noise_z = (static_cast<f64>(z + this->y) / 16.0f);

            f64 value = noise.eval(noise_x, noise_z);
            u32 height = static_cast<u32>(((value + 1) / 2) * CHUNK_SIZE_XZ);
            for (u32 y = 0; y < CHUNK_SIZE_Y; y++) {
                if (y == height) this->tiles[x][y][z].id = TileID::Sand;
                if (y < height) this->tiles[x][y][z].id = TileID::Dirt;
            }
        }
    }
}

void Chunk::mesh() {
    for (u32 x = 0; x < CHUNK_SIZE_XZ; x++) {
        for (u32 y = 0; y < CHUNK_SIZE_Y; y++) {
            for (u32 z = 0; z < CHUNK_SIZE_XZ; z++) {
                TileID id = this->tile_id(x, y, z);
                if (id == TileID::Air) continue;
                TileInfo &info = state->tile_manager.get(id);

                u8 adjacent = this->adjacency_test(x, y, z);
                if (adjacent & 0x01)
                    this->add_cube_left(x, y, z, info.faces[LEFT], 0x2a);
                if (adjacent & 0x02)
                    this->add_cube_right(x, y, z, info.faces[RIGHT], 0x2a);
                if (adjacent & 0x04)
                    this->add_cube_bottom(x, y, z, info.faces[DOWN], 0x15);
                if (adjacent & 0x08)
                    this->add_cube_top(x, y, z, info.faces[UP], 0x3f);
                if (adjacent & 0x10)
                    this->add_cube_back(x, y, z, info.faces[BACK], 0x2a);
                if (adjacent & 0x20)
                    this->add_cube_front(x, y, z, info.faces[FRONT], 0x2a);
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
    u8 z,
    u16 texture_id,
    u8 lighting,
    u8 index) const {
    return
        x | z << 6 | texture_id << 12 | lighting << 24 | index << 30;
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
    bool get_from_other_chunk = false;
    i64 chunk_x = this->x;
    i64 chunk_z = this->y;

    if (x >= CHUNK_SIZE_XZ) {
        x = x - CHUNK_SIZE_XZ;
        get_from_other_chunk = true;
        chunk_x = this->x + CHUNK_SIZE_XZ;
    } if (z >= CHUNK_SIZE_XZ) {
        z = z - CHUNK_SIZE_XZ;
        get_from_other_chunk = true;
        chunk_z = this->y + CHUNK_SIZE_XZ;
    } if (x < 0) {
        x = CHUNK_SIZE_XZ + x;
        get_from_other_chunk = true;
        chunk_x = this->x - CHUNK_SIZE_XZ;
    } if (z < 0) {
        z = CHUNK_SIZE_XZ + z;
        get_from_other_chunk = true;
        chunk_z = this->y - CHUNK_SIZE_XZ;
    }

    if (y < 0) return TileID::Grass;
    if (y >= CHUNK_SIZE_Y) return TileID::Air;

    if (get_from_other_chunk) {
        return state->world.get_level_tile_id(chunk_x, chunk_z, x, y, z);
    }

    return this->tiles[x][y][z].id;
}

void Chunk::add_cube_bottom(u32 x, u32 y, u32 z, u32 t, u8 l) {
    this->solid_mesh.push<u32>({
        this->compress_vertex(x, z, t, l, 3), y,
        this->compress_vertex(x + 1, z, t, l, 2), y,
        this->compress_vertex(x + 1, z + 1, t, l, 1), y,
        this->compress_vertex(x + 1, z + 1, t, l, 1), y,
        this->compress_vertex(x, z + 1, t, l, 0), y,
        this->compress_vertex(x, z, t, l, 3), y
    }, 6);
}

void Chunk::add_cube_top(u32 x, u32 y, u32 z, u32 t, u8 l) {
    this->solid_mesh.push<u32>({
        this->compress_vertex(x, z, t, l, 3), y + 1,
        this->compress_vertex(x + 1, z, t, l, 2), y + 1,
        this->compress_vertex(x + 1, z + 1, t, l, 1), y + 1,
        this->compress_vertex(x + 1, z + 1, t, l, 1), y + 1,
        this->compress_vertex(x, z + 1, t, l, 0), y + 1,
        this->compress_vertex(x, z, t, l, 3), y + 1
    }, 6);
}

void Chunk::add_cube_back(u32 x, u32 y, u32 z, u32 t, u8 l) {
    this->solid_mesh.push<u32>({
        this->compress_vertex(x, z, t, l, 0), y,
        this->compress_vertex(x + 1, z, t, l, 1), y,
        this->compress_vertex(x + 1, z, t, l, 2), y + 1,
        this->compress_vertex(x + 1, z, t, l, 2), y + 1,
        this->compress_vertex(x, z, t, l, 3), y + 1,
        this->compress_vertex(x, z, t, l, 0), y
    }, 6);
}

void Chunk::add_cube_front(u32 x, u32 y, u32 z, u32 t, u8 l) {
    this->solid_mesh.push<u32>({
        this->compress_vertex(x, z + 1, t, l, 0), y,
        this->compress_vertex(x + 1, z + 1, t, l, 1), y,
        this->compress_vertex(x + 1, z + 1, t, l, 2), y + 1,
        this->compress_vertex(x + 1, z + 1, t, l, 2), y + 1,
        this->compress_vertex(x, z + 1, t, l, 3), y + 1,
        this->compress_vertex(x, z + 1, t, l, 0), y
    }, 6);
}

void Chunk::add_cube_left(u32 x, u32 y, u32 z, u32 t, u8 l) {
    this->solid_mesh.push<u32>({
        this->compress_vertex(x, z + 1, t, l, 2), y + 1,
        this->compress_vertex(x, z, t, l, 3), y + 1,
        this->compress_vertex(x, z, t, l, 0), y,
        this->compress_vertex(x, z, t, l, 0), y,
        this->compress_vertex(x, z + 1, t, l, 1), y,
        this->compress_vertex(x, z + 1, t, l, 2), y + 1
    }, 6);
}

void Chunk::add_cube_right(u32 x, u32 y, u32 z, u32 t, u8 l) {
    this->solid_mesh.push<u32>({
        this->compress_vertex(x + 1, z + 1, t, l, 2), y + 1,
        this->compress_vertex(x + 1, z, t, l, 3), y + 1,
        this->compress_vertex(x + 1, z, t, l, 0), y,
        this->compress_vertex(x + 1, z, t, l, 0), y,
        this->compress_vertex(x + 1, z + 1, t, l, 1), y,
        this->compress_vertex(x + 1, z + 1, t, l, 2),y + 1
    }, 6);
}

void Chunk::destroy() {
    this->solid_mesh.destroy();
    for (i32 i = 0; i < CHUNK_SIZE_XZ; i++) {
        for (i32 j = 0; j < CHUNK_SIZE_Y; j++) {
            delete[] this->tiles[i][j];
        }
        delete[] this->tiles[i];
    }
    delete[] this->tiles;
}
