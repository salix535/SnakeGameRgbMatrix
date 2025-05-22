#include "random_pixel.h"
#include "esp_system.h"  

Pixel get_random_free_pixel(const std::unordered_set<Pixel>& free_pixels) {
    std::mt19937 gen;
    gen.seed(esp_random());
    std::vector<Pixel> pixel_list(free_pixels.begin(), free_pixels.end());
    std::uniform_int_distribution<> distrib(0, pixel_list.size() - 1);
    return pixel_list[distrib(gen)];
}