#pragma once

#include "backend/types/vec.hpp"
#include <cstdlib>

namespace Math
{
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
template <typename T>
inline void bresenhamLine(Vec2<int> p1, Vec2<int> p2, T &function)
{
    int dx = std::abs(p2.x - p1.x);
    int dy = -std::abs(p2.y - p1.y);

    int sx = p1.x < p2.x ? 1 : -1;
    int sy = p1.y < p2.y ? 1 : -1;

    int error = dx + dy;

    while (true)
    {
        if (!function(p1.x, p1.y))
        {
            break;
        }

        int e2 = 2 * error;
        if (e2 >= dy)
        {
            if (p1.x == p2.x)
            {
                break;
            }
            error = error + dy;
            p1.x = p1.x + sx;
        }
        if (e2 <= dx)
        {
            if (p1.y == p2.y)
            {
                break;
            }

            error = error + dx;
            p1.y = p1.y + sy;
        }
    }
}
} // namespace Math
