#include "chunk.hpp"

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
                this->tiles[x][z][i].id = TileID::Grass;
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
    for (float i = 0; i < CHUNK_SIZE_XYZ; i += 1.0f) {
        for (float j = 0; j < CHUNK_SIZE_XYZ; j += 1.0f) {
            for (float k = 0; k < CHUNK_SIZE_XYZ; k += 1.0f) {
                this->solid_mesh.push<float>({
                    i + 1.0f,  j + 1.0f, k,  1.0f, 1.0f,
                    i + 1.0f, j, k,  1.0f, 0.0f,
                    i,  j + 1.0f, k,  0.0f, 1.0f,
                    i + 1.0f, j, k,  1.0f, 0.0f,
                    i, j, k, 0.0f, 0.0f,
                    i, j + 1.0f, k,  0.0f, 1.0f
                }, 6);
            }
        }
    }

    // construct the mesh
    this->solid_mesh.build();
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
