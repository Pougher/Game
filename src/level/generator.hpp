#pragma once

#include <vector>

#include "chunk.hpp"
#include "generator_pass.hpp"

#include "../common/types.hpp"
#include "../common/open_simplex_noise.hpp"

namespace level {

struct Generator {
    // a generator holds a vector of generator passes that are ordered and
    // applied to the chunk in that order
    std::vector<GeneratorPass*> passes;

    // copies a vector of generator passes into our pass variable
    Generator(const std::vector<GeneratorPass*>&);

    // does nothing
    Generator();

    // sets the passes vector
    void set_passes(const std::vector<GeneratorPass*>&);

    // runs all of the generator passes on the chunk
    void run(Chunk*);
};

}
