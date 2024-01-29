#include "tile_manager.hpp"

TileManager::TileManager() {
    this->tiles.resize(TILE_MANAGER_TILE_CAP);
}

void TileManager::register_tile(TileID id, const TileInfo &tile) {
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
        { FORWARD,  texture }
    };
}

TileInfo& TileManager::get(TileID tile) {
    return this->tiles[tile];
}
