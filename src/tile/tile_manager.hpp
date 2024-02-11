#pragma once

#include <vector>

#include "tile.hpp"

#define TILE_MANAGER_TILE_CAP 1024

struct TileManager {
    // vector containing the tiles that we are using
    TileInfo *tiles;

    // simple constructor that reserves TILE_CAP number of spaces in the tiles
    // vector
    TileManager();

    // registers a new tile to the tile manager
    void register_tile(TileID, const TileInfo&);

    // registers a default tile into the tile manager (no faces map is needed),
    // that will be constructed by the function
    void register_default_tile(TileID, const TileInfo&, int);

    // returns a reference to a TileID object
    TileInfo& get(TileID);

    // gets the transparency attribute of a specific tile ID
    bool get_transparent(TileID);

    // cleans up allocated data in the tile manager
    void destroy();
};

// register a tile to the tile manager
#define REGISTER_TILE(name) \
    extern void tile_##name##_register(TileManager*); \
    tile_##name##_register(this)

