#include "generator.hpp"


using namespace level;

Generator::Generator(const std::vector<GeneratorPass*> &p) : passes(p) {}
Generator::Generator() {}

void Generator::set_passes(const std::vector<GeneratorPass*> &passes) {
    this->passes = passes;
}

void Generator::run(Chunk *chunk) {
    OpenSimplexNoise::Noise noise(69);

    f64 **heightmap = new f64 *[CHUNK_SIZE_XZ];
    for (i32 i = 0; i < CHUNK_SIZE_XZ; i++) {
        heightmap[i] = new f64[CHUNK_SIZE_XZ];
        for (i32 j = 0; j < CHUNK_SIZE_XZ; j++) {
            f64 noise_x = i + chunk->x;
            f64 noise_y = j + chunk->y;

            heightmap[i][j] = noise.eval(noise_x / 16.0f, noise_y / 16.0f);
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
