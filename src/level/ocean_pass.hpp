#pragma once

#include "../common/types.hpp"

#include "generator_pass.hpp"
#include "chunk.hpp"

namespace level {

struct OceanPass : GeneratorPass {
    // ocean pass that builds oceans and lakes
    void pass(Chunk*, f64**);
};

}
