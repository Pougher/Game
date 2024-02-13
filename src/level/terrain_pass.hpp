#pragma once

#include "../common/types.hpp"

#include "generator_pass.hpp"
#include "chunk.hpp"

namespace level {

struct TerrainPass : GeneratorPass {
    // terrain pass builds things like mountain terrain and grass etc.
    void pass(Chunk*, f64**);
};

}
