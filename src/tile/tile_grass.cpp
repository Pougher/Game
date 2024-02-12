#include "tile_manager.hpp"

void tile_grass_register(TileManager *tm) {
    const TileInfo ti = {
        .transparent = false,
        .fluid = false,
        .faces = {
            { UP, 2 },
            { DOWN, 0 },
            { LEFT, 1 },
            { RIGHT, 1 },
            { BACK, 1 },
            { FRONT, 1 },
        }
    };

    tm->register_tile(TileID::Grass, ti);
}
