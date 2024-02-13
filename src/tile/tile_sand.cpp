#include "tile_manager.hpp"

void tile_sand_register(TileManager *tm) {
    const TileInfo ti = {
        .transparent = false,
        .fluid = false,
        .faces = {
            { UP, 3 },
            { DOWN, 3 },
            { LEFT, 3 },
            { RIGHT, 3 },
            { BACK, 3 },
            { FRONT, 3 },
        }
    };

    tm->register_tile(TileID::Sand, ti);
}
