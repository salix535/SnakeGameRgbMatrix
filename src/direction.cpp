#include "direction.h"

Direction get_opposite(Direction dir) {
    switch (dir) {
        case Direction::Up:    return Direction::Down;
        case Direction::Down:  return Direction::Up;
        case Direction::Left:  return Direction::Right;
        case Direction::Right: return Direction::Left;
    }
    return dir; // Fallback should not happen.
}

const char* directionToString(Direction dir) {
    switch (dir) {
        case Direction::Up:    return "Up";
        case Direction::Down:  return "Down";
        case Direction::Left:  return "Left";
        case Direction::Right: return "Right";
        default:               return "Unknown";
    }
}