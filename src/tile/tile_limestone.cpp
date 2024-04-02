#include "tile_manager.hpp"

void tile_limestone_register(TileManager *tm) {
    const TileInfo ti = {
        .transparent = false,
        .fluid = false
    };

    tm->register_default_tile(TileID::Limestone, ti, 5);
}
