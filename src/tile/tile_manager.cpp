#include "tile_manager.hpp"
#include <iostream>

TileManager::TileManager() {
    this->tiles = new TileInfo[TILE_MANAGER_TILE_CAP];

    REGISTER_TILE(grass);
    REGISTER_TILE(air);
    REGISTER_TILE(dirt);
    REGISTER_TILE(sand);
    REGISTER_TILE(water);
    REGISTER_TILE(limestone);
}

void TileManager::register_tile(TileID id, const TileInfo& tile) {
    // inserts a tile at the specified tile location
    this->tiles[id] = tile;
}

void TileManager::register_default_tile(
    TileID id,
    const TileInfo &tile,
    int texture) {
    // copy the tile into the internal vector
    this->tiles[id] = tile;

    // set the faces to just the face ID at all directions
    this->tiles[id].faces = {
        { UP,       texture },
        { DOWN,     texture },
        { LEFT,     texture },
        { RIGHT,    texture },
        { BACK,     texture },
        { FRONT,    texture }
    };
}

TileInfo& TileManager::get(TileID tile) {
    return this->tiles[tile];
}

bool TileManager::get_transparent(TileID tile) {
    return this->tiles[tile].transparent;
}

void TileManager::destroy() {
    delete[] this->tiles;
}
