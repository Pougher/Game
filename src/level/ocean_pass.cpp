#include "ocean_pass.hpp"

using namespace level;

void OceanPass::pass(Chunk *chunk, f64 **noise) {
    (void) noise;
    for (u32 i = 0; i < CHUNK_SIZE_XZ; i++) {
        for (u32 j = 0; j < CHUNK_SIZE_XZ; j++) {
            for (u32 k = 0; k < 90; k++) {
                chunk->tiles[i][k][j].id = TileID::Water;
            }
        }
    }
}
