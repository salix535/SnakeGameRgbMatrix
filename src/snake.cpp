#include "snake.h"
#include "Arduino.h"

const u8_t Snake::INITIAL_SNAKE_SIZE = 5;

Snake::Snake() {
    initialise();
}

void Snake::initialise() {
    pixels.clear();
    for (int i = 0; i < INITIAL_SNAKE_SIZE; i++) {
        Pixel p = Pixel(i, 0);
        pixels.push_front(p);
        pixel_set.insert(p);
    }
    pixel_to_remove = pixels.back();
}

Pixel Snake::get_pixel_to_remove() const {
    return pixel_to_remove;
}

MoveResult Snake::move_snake(Direction direction, Pixel apple) {
    Pixel head = pixels.front();
    Pixel new_head = head.moved(direction);
    if (pixel_set.count(new_head)) {
        return {Pixel(-1, -1), false};
    }
    bool apple_was_eaten = true;
    if (!(new_head == apple)) {
        pixel_to_remove = pixels.back();    
        pixel_set.erase(pixel_to_remove);
        pixels.pop_back();
        apple_was_eaten = false;
    }
    pixels.push_front(new_head);
    pixel_set.insert(new_head);
    return {new_head, apple_was_eaten};
}

std::deque<Pixel> Snake::get_pixels() const {
    return pixels;
}
