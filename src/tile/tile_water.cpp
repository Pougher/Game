#include "tile_manager.hpp"

void tile_water_register(TileManager *tm) {
    const TileInfo ti = {
        .transparent = false,
        .fluid = false
    };

    tm->register_default_tile(TileID::Water, ti, 4);
}
