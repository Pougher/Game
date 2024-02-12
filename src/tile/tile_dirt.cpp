#include "tile_manager.hpp"

void tile_dirt_register(TileManager *tm) {
    const TileInfo ti = {
        .transparent = false,
        .fluid = false
    };

    tm->register_default_tile(TileID::Dirt, ti, 0);
}
