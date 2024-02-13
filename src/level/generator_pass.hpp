#pragma once

#include "../common/types.hpp"
#include "chunk.hpp"

namespace level {

struct GeneratorPass {
    // runs a generator pass on the chunks tiles using the heightmap
    virtual void pass(Chunk*, f64**) = 0;

    // set default destructor
    virtual ~GeneratorPass() = default;
};

}
