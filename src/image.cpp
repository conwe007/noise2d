#include "image.h"
#include <iostream>

Color::Color()
{
    r = 0;
    g = 0;
    b = 0;
    a = Color::CHANNEL_MAX;
    return;
}

Color::Color(int16_t r, int16_t g, int16_t b, int16_t a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    return;
}

// initializes empty image
Image::Image()
{
    pixels.resize(0);
    width = 0;
    height = 0;
    return;
}

// saves a png to the specified path
size_t Image::save(const char* file_name)
{
    size_t error = lodepng::encode(file_name, pixels, width, height);

    if(error)
    {
        std::cout << "error: save - " << error << ": "<< lodepng_error_text(error) << std::endl;
    }

    return error;
}

// fills image with a grayscale representation of specified threshold map
void Image::create_from_matrix(std::vector<std::vector<int>> matrix)
{
    height = matrix.size();
    width = matrix[0].size();
    pixels.resize(width * height * Color::NUM_BYTES_COLOR);

    for(size_t y = 0; y < height; y++)
    {
        for(size_t x = 0; x < width; x++)
        {
            int index_pixels = Color::NUM_BYTES_COLOR * width * y + Color::NUM_BYTES_COLOR * x;
            pixels[index_pixels + 0] = matrix[y][x];
            pixels[index_pixels + 1] = matrix[y][x];
            pixels[index_pixels + 2] = matrix[y][x];
            pixels[index_pixels + 3] = Color::CHANNEL_MAX;
        }
    }

    return;
}
