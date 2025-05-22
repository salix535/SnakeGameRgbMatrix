#pragma once

#include <unordered_set>
#include <vector>
#include <random>
#include "types.h"

Pixel get_random_free_pixel(const std::unordered_set<Pixel>& free_pixels);
