#include "fftw3.h" // for dft functions
#include "fourier.h" // dft wrapper
#include "image.h" // png encoder/decoder wrapper
#include "lodepng.h" // png encoder/decoder
#include "noise2d.h" // noise generation functions
#include <chrono> // clock_t, clock()
#include <iostream> // std::cout, std::endl

std::vector<std::vector<int>> create_matrix_from_noise(Noise2D<int> noise, size_t width, size_t height);
std::string generate_white_noise(int width, int height, int output_levels, bool fourier, bool benchmark);

int main()
{
    size_t output_levels = 256;
    bool fourier = true;
    bool benchmark = true;

    std::cout << generate_white_noise(2, 2, output_levels, fourier, benchmark) << std::endl;
    std::cout << generate_white_noise(4, 4, output_levels, fourier, benchmark) << std::endl;
    std::cout << generate_white_noise(8, 8, output_levels, fourier, benchmark) << std::endl;
    std::cout << generate_white_noise(16, 16, output_levels, fourier, benchmark) << std::endl;
    std::cout << generate_white_noise(32, 32, output_levels, fourier, benchmark) << std::endl;
    std::cout << generate_white_noise(64, 64, output_levels, fourier, benchmark) << std::endl;

    return 0;
}

std::string generate_white_noise(int width, int height, int output_levels, bool fourier, bool benchmark)
{
    std::string output = "";
    std::chrono::time_point<std::chrono::steady_clock> time_start;
    std::chrono::time_point<std::chrono::steady_clock> time_end;
    Noise2D<int> white_noise = Noise2D<int>(width, height, output_levels);
    Image image = Image();
    char file_name[1000];
    sprintf(file_name, "output\\white_noise_%ix%i.png", width, height);

    if(benchmark)
    {
        char heading[100];
        sprintf(heading, "%ix%i time: ", width, height);
        output += heading;
        time_start = std::chrono::steady_clock::now();
    }

    white_noise.generate_white_noise();

    if(benchmark)
    {
        time_end = std::chrono::steady_clock::now();
        output += std::to_string(std::chrono::nanoseconds(time_end - time_start).count() / 1000) + " us\n";
    }

    std::vector<std::vector<int>> matrix = create_matrix_from_noise(white_noise, width, height);
    image.create_from_matrix(matrix);
    image.save(file_name);

    if(fourier)
    {
        if(benchmark)
        {
            char heading[100];
            sprintf(heading, "%ix%i fourier time: ", width, height);
            output += heading;
            time_start = std::chrono::steady_clock::now();
        }

        Fourier2D fourier_2d = Fourier2D(matrix, true, true);
        fourier_2d.dft();
        fourier_2d.normalize_transform(output_levels);

        if(benchmark)
        {
            time_end = std::chrono::steady_clock::now();
            output += std::to_string(std::chrono::nanoseconds(time_end - time_start).count() / 1000) + " us\n";
        }

        sprintf(file_name, "output\\white_noise_%ix%i_fourier.png", width, height);
        image.create_from_matrix(fourier_2d.get_transform());
        image.save(file_name);
    }

    return output;
}

std::vector<std::vector<int>> create_matrix_from_noise(Noise2D<int> noise, size_t width, size_t height)
{
    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));

    for(size_t y = 0; y < height; y++)
    {
        for(size_t x = 0; x < width; x++)
        {
            matrix[y][x] = noise.get_noise_at(x, y);
        }
    }

    return matrix;
}
