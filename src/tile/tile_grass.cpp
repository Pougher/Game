#include "tile_manager.hpp"

void tile_grass_register(TileManager *tm) {
    const TileInfo ti = {
        .transparent = false,
        .fluid = false,
        .faces = {
            { UP, 240 },
            { DOWN, 240 },
            { LEFT, 240 },
            { RIGHT, 240 },
            { BACK, 240 },
            { FORWARD, 240 },
        }
    };

    tm->register_tile(TileID::Grass, ti);
}
