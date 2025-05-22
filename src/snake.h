#pragma once
#include <deque>
#include "types.h"
#include <Arduino.h>
#include <unordered_set>

class Snake {
public:
    static const u8_t INITIAL_SNAKE_SIZE;

    Snake();
    Pixel get_pixel_to_remove() const;
    MoveResult move_snake(Direction direction, Pixel apple);
    std::deque<Pixel> get_pixels() const;

private:
    std::deque<Pixel> pixels;
    std::unordered_set<Pixel> pixel_set;
    Pixel pixel_to_remove;
    void initialise();
};