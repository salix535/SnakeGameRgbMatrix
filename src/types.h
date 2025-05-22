#pragma once
#include <config.h>
#include <direction.h>
#include <deque>
#include <functional>

struct Pixel
{
    int x;
    int y;

    constexpr Pixel(int x = 0, int y = 0) : x(x), y(y) {}

    Pixel moved(Direction dir) const
    {
        int newX = x;
        int newY = y;

        switch (dir)
        {
        case Direction::Up:
            newY -= 1;
            break;
        case Direction::Down:
            newY += 1;
            break;
        case Direction::Left:
            newX -= 1;
            break;
        case Direction::Right:
            newX += 1;
            break;
        }

        // Wrap around horizontally
        if (newX < 0)
        {
            newX = PANEL_RES_X - 1;
        }
        else if (newX >= PANEL_RES_X)
        {
            newX = 0;
        }

        // Wrap around vertically
        if (newY < 0)
        {
            newY = PANEL_RES_Y - 1;
        }
        else if (newY >= PANEL_RES_Y)
        {
            newY = 0;
        }

        return Pixel(newX, newY);
    }

    bool operator==(const Pixel &other) const
    {
        return x == other.x && y == other.y;
    }
};

struct MoveResult {
    Pixel new_head;
    bool ate_apple;
};

namespace std
{
    template <>
    struct hash<Pixel>
    {
        std::size_t operator()(const Pixel &p) const
        {
            return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
        }
    };
}
