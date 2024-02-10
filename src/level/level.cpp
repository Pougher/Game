#include "level.hpp"

using namespace level;

Level::Level(u32 vd) : view_distance(vd) {
    this->loaded_chunks = new Chunk *[vd];
    for (u32 i = 0; i < vd; i++) {
        this->loaded_chunks[i] = new Chunk[vd];
    }
}

void Level::render() {
    for (u32 i = 0; i < this->view_distance; i++) {
        for (u32 j = 0; j < this->view_distance; j++) {
            this->loaded_chunks[i][j].render();
        }
    }
}

void Level::generate() {
}

void Level::mesh() {
    for (u32 i = 0; i < this->view_distance; i++) {
        for (u32 j = 0; j < this->view_distance; j++) {
            this->loaded_chunks[i][j].mesh();
        }
    }
}

void Level::cleanup() {
    for (u32 i = 0; i < this->view_distance; i++) {
        delete[] this->loaded_chunks[i];
    }
    delete[] this->loaded_chunks;
}
