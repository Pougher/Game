#include "terrain_pass.hpp"

using namespace level;

void TerrainPass::pass(Chunk *chunk, f64 **noise) {
    for (u32 i = 0; i < CHUNK_SIZE_XZ; i++) {
        for (u32 j = 0; j < CHUNK_SIZE_XZ; j++) {
            u32 y_value = static_cast<u32>(
                (noise[i][j] + 1.0) * (CHUNK_SIZE_Y / 128)
            );
            for (u32 k = 0; k < y_value; k++)
                chunk->tiles[i][k][j].id = TileID::Dirt;
            chunk->tiles[i][y_value][j].id = TileID::Grass;
        }
    }
}
