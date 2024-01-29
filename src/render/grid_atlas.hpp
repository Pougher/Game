#pragma once

#include <memory>
#include <iostream>
#include <cstring>

#include "../common/log.hpp"

#include "array_texture.hpp"

namespace rac {

struct GridAtlas {
    std::unique_ptr<ArrayTexture> array_texture;

    // width and height of the tiles in the array texture
    int tile_width, tile_height;

    // the number of tiles in the X and Y direction of the atlas
    int tile_x, tile_y;

    // the number of colour channels in the image
    int channels;

    // constructor for generating a grid atlas from an image path
    GridAtlas(const std::string&, int, int, int, int);

    // constructor for generating a grid atlas from some already existing,
    // correctly formatted data

    // destroys the grid atlas
    void destroy();
};

}
