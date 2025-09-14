#ifndef __IMAGE_H
#define __IMAGE_H

#include "lodepng.h" // png encode/decode functions
#include <cstdint> // int16_t
#include <vector> // std::vector

struct Color
{
    Color();
    Color(int16_t r, int16_t g, int16_t b, int16_t a);

    static inline constexpr int NUM_BYTES_COLOR = 4;
    static inline constexpr int INDEX_R = 0;
    static inline constexpr int INDEX_G = 1;
    static inline constexpr int INDEX_B = 2;
    static inline constexpr int INDEX_A = 3;
    static inline constexpr int CHANNEL_MAX = 255;

    int16_t r;
    int16_t g;
    int16_t b;
    int16_t a;
};

class Image
{
public:
    Image();
    size_t save(const char* file_name);
    void create_from_matrix(std::vector<std::vector<int>> matrix);

private:
    std::vector<unsigned char> pixels;
    unsigned int width;
    unsigned int height;
};

#endif
