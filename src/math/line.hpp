#pragma once

#include "math/vec.hpp"
#include <cmath>

namespace Math
{
namespace Line
{
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
template <typename Function>
inline void bresenhamLine(Vec2i p1, const Vec2i &p2, Function &&function)
{
    int dx = std::abs(p2.x - p1.x);
    int dy = -std::abs(p2.y - p1.y);
    int sx = p1.x < p2.x ? 1 : -1;
    int sy = p1.y < p2.y ? 1 : -1;

    int error = dx + dy;

    while (true)
    {
        if (function(p1))
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
            p1.x += sx;
        }
        if (e2 <= dx)
        {
            if (p1.y == p2.y)
            {
                break;
            }

            error = error + dx;
            p1.y += sy;
        }
    }
}

template <typename HitCheckFunction>
inline void bresenhamRaycast(const Vec2i &start, float angle,
                             HitCheckFunction &&function, int maxDistance = 100)
{
    int endX = start.x + std::cosf(angle) * maxDistance;
    int endY = start.y + std::sinf(angle) * maxDistance;
    Vec2i end = Vec2i(endX, endY).toGrid();
    bresenhamLine(start, end, function);
}
} // namespace Line
} // namespace Math
