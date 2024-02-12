#include "tile_manager.hpp"

void tile_air_register(TileManager *tm) {
    const TileInfo ti = {
        .transparent = true,
        .fluid = false,
        .faces = {
            { UP, 0 },
            { DOWN, 0 },
            { LEFT, 0 },
            { RIGHT, 0 },
            { BACK, 0 },
            { FRONT, 0 },
        }
    };

    tm->register_tile(TileID::Air, ti);
}
