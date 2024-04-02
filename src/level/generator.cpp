#include "generator.hpp"


using namespace level;

Generator::Generator(const std::vector<GeneratorPass*> &p) : passes(p) {}
Generator::Generator() {}

void Generator::set_passes(const std::vector<GeneratorPass*> &passes) {
    this->passes = passes;
    this->noise_generator.set_seed(69);
}

constexpr f64 Generator::octave_noise(
    f64 x,
    f64 y,
    f64 amplitude,
    f64 frequency,
    i32 octaves,
    f64 persistence,
    f64 lancunarity) {
    f64 value = 0;

    for (i32 i = 0; i < octaves; i++) {
        value += amplitude * this->noise_generator.eval(
            x * frequency,
            y * frequency
        );
        amplitude *= persistence;
        frequency *= lancunarity;
    }

    return value;
}

void Generator::run(Chunk *chunk) {
    f64 **heightmap = new f64 *[CHUNK_SIZE_XZ];
    for (i32 i = 0; i < CHUNK_SIZE_XZ; i++) {
        heightmap[i] = new f64[CHUNK_SIZE_XZ];
        for (i32 j = 0; j < CHUNK_SIZE_XZ; j++) {
            f64 noise_x = i + chunk->x;
            f64 noise_y = j + chunk->y;

            heightmap[i][j] = this->noise_generator.eval(
                noise_x / 32,
                noise_y / 32
            );

            //heightmap[i][j] = this->octave_noise(
            //    noise_x,
            //    noise_y,
            //    1,
            //    0.01,
            //    4,
            //    0.5,
            //    2.0
            //);
        }
    }

    for (const auto &pass : this->passes) {
        pass->pass(chunk, heightmap);
    }

    for (i32 i = 0; i < CHUNK_SIZE_XZ; i++) {
        delete[] heightmap[i];
    }
    delete[] heightmap;
}

void Generator::set_seed(f64 seed) {
    this->seed = seed;
}
