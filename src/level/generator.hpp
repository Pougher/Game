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

    // the nosie generator that produces noise values from a seed
    OpenSimplexNoise::Noise noise_generator;

    // the seed of the level generator
    f64 seed;

    // copies a vector of generator passes into our pass variable
    Generator(const std::vector<GeneratorPass*>&);

    // does nothing
    Generator();

    // sets the passes vector
    void set_passes(const std::vector<GeneratorPass*>&);

    // produces a noise value dependant on multiple different levels of noise
    // lancunarity defines how frequency should increase as the octaves
    // increase, and persistence defines how much amplitude should diminish
    // as octaves increase
    constexpr f64 octave_noise(f64, f64, f64, f64, i32, f64, f64);

    // sets the seed for the noise generator, and the seed value for the
    // entire generator object
    void set_seed(f64);

    // runs all of the generator passes on the chunk
    void run(Chunk*);
};

}
