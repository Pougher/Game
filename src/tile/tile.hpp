#pragma once

#include <bitset>
#include <unordered_map>

#include "../common/types.hpp"
#include "../common/direction.hpp"

// enum to hold the different types of block
enum TileID {
    Grass       = 0,
    Air         = 1,
};

// holds the state of tiles, each bit represents a different tile attribute
enum TileState {
    None        = 0x00000000
};

struct Tile {
    // the identifier of the tile
    TileID id;

    // the bitset representing the state of the tile
    std::bitset<32> state;
};

struct TileInfo {
    // if the block is transparent
    bool transparent;

    // if the block counts as a fluid
    bool fluid;

    // stores a map for the faces of a block depending on the direction of the
    // face being generated
    std::unordered_map<Direction, int> faces;
};
