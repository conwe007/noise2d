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
    void clear();
    size_t get_width();
    size_t get_height();
    size_t load(const char* file_name);
    size_t save(const char* file_name);
    Color get_pixel(unsigned int x, unsigned int y);
    void set_pixel(Color color, unsigned int x, unsigned int y);
    std::vector<std::vector<int>> gradient_map();
    void create_from_threshold_matrix(std::vector<std::vector<int>> threshold_matrix);
    std::vector<std::vector<int>> get_threshold_matrix_from_image();

private:
    std::vector<unsigned char> pixels;
    unsigned int width;
    unsigned int height;
};

#endif
