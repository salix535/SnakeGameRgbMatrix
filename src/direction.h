enum class Direction {
    Up,
    Down,
    Left,
    Right
};

Direction get_opposite(Direction direction);
Direction randomDirection(Direction current_direction);
const char* directionToString(Direction dir);