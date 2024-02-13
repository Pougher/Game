#include "level.hpp"
#include "../common/global.hpp"

using namespace level;

Level::Level(u32 vd, const std::vector<GeneratorPass*> &passes)
    : corner_x(0),
      corner_y(0),
      view_distance(vd) {
    this->init_chunks();
    this->level_generator.set_passes(passes);
}

Level::Level(u32 vd) : corner_x(0),
                       corner_y(0),
                       view_distance(vd) {
    this->init_chunks();
}

void Level::init_chunks() {
    this->loaded_chunks = new Chunk **[this->view_distance];
    for (u32 i = 0; i < this->view_distance; i++) {
        this->loaded_chunks[i] = new Chunk*[this->view_distance];
        for (u32 j = 0; j < this->view_distance; j++) {
            this->loaded_chunks[i][j] = new Chunk;
            this->loaded_chunks[i][j]->x = i * CHUNK_SIZE_XZ;
            this->loaded_chunks[i][j]->y = j * CHUNK_SIZE_XZ;
        }
    }
}

void Level::render() {
    for (u32 i = 0; i < this->view_distance; i++) {
            for (u32 j = 0; j < this->view_distance; j++) {
            state->shaders["chunk"].set_vec2(
                "chunk_pos",
                glm::vec2(
                    i * CHUNK_SIZE_XZ + this->corner_x,
                    j * CHUNK_SIZE_XZ + this->corner_y
                )
            );
            this->loaded_chunks[i][j]->render();
        }
    }
}

TileID Level::get_level_tile_id(i64 cx, i64 cy, u32 x, u32 y, u32 z) {
    if (cx < this->corner_x || cy < this->corner_y
        || cx >= this->corner_x + CHUNK_SIZE_XZ * this->view_distance
        || cy >= this->corner_y + CHUNK_SIZE_XZ * this->view_distance) {
        return TileID::Grass;
    }
    u32 index_x = (cx - this->corner_x) / CHUNK_SIZE_XZ;
    u32 index_y = (cy - this->corner_y) / CHUNK_SIZE_XZ;

    return this->loaded_chunks[index_x][index_y]->tile_id(x, y, z);
}

void Level::generate() {
    for (u32 i = 0; i < this->view_distance; i++) {
        for (u32 j = 0; j < this->view_distance; j++) {
            this->level_generator.run(this->loaded_chunks[i][j]);
        }
    }
}

void Level::mesh() {
    for (u32 i = 0; i < this->view_distance; i++) {
        for (u32 j = 0; j < this->view_distance; j++) {
            this->loaded_chunks[i][j]->mesh();
        }
    }
}

void Level::move(i64 x, i64 y) {
    Chunk **old = new Chunk*[this->view_distance * this->view_distance];

    // some of the edge chunks might need to be updated
    std::vector<Chunk*> mesh_update_chunks = this->get_edge_chunks();

    this->corner_x = x;
    this->corner_y = y;

    // copy data into old
    for (u32 i = 0; i < this->view_distance; i++) {
        std::memcpy(
            (char*)old + i * sizeof(Chunk*) * this->view_distance,
            this->loaded_chunks[i],
            sizeof(Chunk*) * this->view_distance
        );
        std::memset(
            this->loaded_chunks[i],
            0,
            sizeof(Chunk*) * this->view_distance
        );
    }

    for (u32 i = 0; i < this->view_distance; i++) {
        for (u32 j = 0; j < this->view_distance; j++) {
            Chunk *c = old[j + i * this->view_distance];
            if (c->x >= this->corner_x && c->y >= this->corner_y &&
                c->x <=
                    (this->corner_x + this->view_distance * CHUNK_SIZE_XZ) &&
                c->y <=
                    (this->corner_y + this->view_distance * CHUNK_SIZE_XZ)) {
                // chunk remains in bounds
                u32 index_x = (c->x - this->corner_x) / CHUNK_SIZE_XZ;
                u32 index_y = (c->y - this->corner_y) / CHUNK_SIZE_XZ;

                this->loaded_chunks[index_x][index_y] = c;
                continue;
            }

            // if the chunk that is being deleted is in our mesh_update_chunks
            // vector, then we need to erase it
            mesh_update_chunks.erase(
                std::remove(
                    mesh_update_chunks.begin(),
                    mesh_update_chunks.end(),
                    c
                ), mesh_update_chunks.end()
            );

            c->destroy();
            delete c;
        }
    }

    // fill in all of the deleted chunks
    for (u32 i = 0; i < this->view_distance; i++) {
        for (u32 j = 0; j < this->view_distance; j++) {
            if (this->loaded_chunks[i][j] == NULL) {
                this->loaded_chunks[i][j] = new Chunk;
                this->loaded_chunks[i][j]->x =
                    i * CHUNK_SIZE_XZ + this->corner_x;
                this->loaded_chunks[i][j]->y =
                    j * CHUNK_SIZE_XZ + this->corner_y;

                this->loaded_chunks[i][j]->generate();
                mesh_update_chunks.push_back(this->loaded_chunks[i][j]);
            }
        }
    }

    // remesh all of the chunks that require it
    for (const auto &c : mesh_update_chunks) {
        c->mesh();
    }

    delete[] old;
}

std::vector<Chunk*> Level::get_edge_chunks() {
    std::vector<Chunk*> edges;

    for (u32 i = 0; i < this->view_distance; i++) {
        for (u32 j = 0; j < this->view_distance; j++) {
            Chunk *c = this->loaded_chunks[i][j];
            if (c->x == this->corner_x || c->x ==
                this->corner_x + (this->view_distance - 1) * CHUNK_SIZE_XZ ||
                c->y == this->corner_y || c->y ==
                this->corner_y + (this->view_distance - 1) * CHUNK_SIZE_XZ) {
                edges.push_back(c);
            }
        }
    }

    return edges;
}

void Level::destroy() {
    for (u32 i = 0; i < this->view_distance; i++) {
        for (u32 j = 0; j < this->view_distance; j++) {
            this->loaded_chunks[i][j]->destroy();
            delete this->loaded_chunks[i][j];
        }
        delete[] this->loaded_chunks[i];
    }
    delete[] this->loaded_chunks;

    for (const auto &pass : this->level_generator.passes) {
        delete pass;
    }
}
