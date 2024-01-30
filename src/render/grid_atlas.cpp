#include "grid_atlas.hpp"
#include "stb_image.h"

using namespace rac;

GridAtlas::GridAtlas(
    const std::string &filepath,
    int tile_width,
    int tile_height,
    int tile_x,
    int tile_y) {
    // load the image data into a buffer
    stbi_set_flip_vertically_on_load(1);

    // temporary variables for storing the width and height of the image (we
    // will need this in a later step)
    int width;
    int height;

    // load the image data from the file
    unsigned char *data = stbi_load(
        filepath.c_str(),
        &width,
        &height,
        &this->channels,
        0
    );

    if (data == NULL) {
        rlog::error("Issue loading image: '" + filepath + "'");
        return;
    }

    // check the image is properly formatted
#ifndef NDEBUG
    assert(
        "ArrayTexture width less than image width" &&
        (width >= (tile_x * tile_width))
    );
    assert(
        "ArrayTexture height less than image height" &&
        (height >= (tile_y * tile_height))
    );
#endif

    // now that we have the data, we can transform it into the correct format
    // for OpenGL to use for array textures
    // first, create a temporary buffer to store our new image data
    unsigned char *atlas = (unsigned char*)calloc(
        sizeof(unsigned char),
        width * height * this->channels
    );

    // copy data correctly into our new buffer
    const int image_row = (width * this->channels);
    const int tile_size_x = (tile_width * this->channels);
    const int tile_size = tile_width * tile_height * this->channels;

    // sorry for this being an unreadable mess, I stole it from one of my old
    // projects and I'm not updating it
    for (int y = 0; y < tile_y; y++) {
        for (int x = 0; x < tile_x; x++) {
            unsigned char *ptr =
                data + (image_row * y * tile_y) + tile_size_x * x;
            unsigned char *aptr = atlas + (y * tile_y + x) * tile_size;

            for (int row = 0; row < tile_width; row++) {
                memcpy(
                    aptr + tile_size_x * row,
                    ptr + (image_row * row),
                    tile_size_x
                );
            }
        }
    }

    // finally, create our array texture
    this->array_texture = std::make_unique<ArrayTexture>(
        atlas,
        tile_width,
        tile_height,
        tile_x * tile_y
    );
#ifndef NDEBUG
    rlog::info("Constructed grid atlas from '" + filepath + "'");
#endif

    free(atlas);
    stbi_image_free(data);
}

GridAtlas::GridAtlas(
    int tile_width,
    int tile_height,
    int tile_x,
    int tile_y,
    unsigned char *data) : tile_width(tile_width),
                           tile_height(tile_height),
                           tile_x(tile_x),
                           tile_y(tile_y) {
    this->array_texture = std::make_unique<ArrayTexture>(
        data,
        tile_width,
        tile_height,
        tile_x * tile_y
    );
}

void GridAtlas::create(
    int tile_width,
    int tile_height,
    int tile_x,
    int tile_y,
    unsigned char *data) {
    this->tile_width = tile_width;
    this->tile_height = tile_height;
    this->tile_x = tile_x;
    this->tile_y = tile_x;

    // create a new array texture
    this->array_texture = std::make_unique<ArrayTexture>(
        data,
        tile_width,
        tile_height,
        tile_x * tile_y
    );
}

void GridAtlas::destroy() {
    this->array_texture->destroy();
    this->array_texture.reset();
}
