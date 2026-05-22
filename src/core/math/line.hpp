#pragma once

#include "core/math/angle.hpp"
#include "core/math/vec.hpp"
#include <cmath>

template <typename T> struct Segment2
{
    Vec2<T> a;
    Vec2<T> b;

    bool operator==(const Segment2 &other)
    {
        return (a == other.a && b == other.b) || (a == other.b && b == other.a);
    }
};

using Segment2i = Segment2<int>;
using Segment2u = Segment2<unsigned int>;
using Segment2f = Segment2<float>;
using Segment2d = Segment2<double>;

struct Line
{
    // form: y = ax + b;
    float a = 0.0f, b = 0.0f;

    Line perpendicular()
    {
        Line out;
        out.a = -a / 2.0f;
        out.b = b;
        return out;
    }

    // https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
    Vec2f intersect(const Line &other)
    {
        Vec2f out;
        out.x = (other.b - b) / (a - other.a);
        out.y = a * (out.x) + b;
        return out;
    }

    void createFromPoints(Vec2f p1, Vec2f p2)
    {
        a = (p2.y - p1.y) / (p2.x - p1.x);
        b = p1.y - a * p1.x;
    }
};

namespace Math
{
namespace Line
{
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
template <typename Function> inline void bresenhamLine(Vec2i p1, Vec2i p2, Function &&function)
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
inline void bresenhamRaycast(Vec2i start, struct Angle angle, HitCheckFunction &&function,
                             int maxDistance = 100)
{
    float radians = angle.radians();

    int endX  = start.x + static_cast<int>(std::floor(std::cosf(radians) * maxDistance));
    int endY  = start.y + static_cast<int>(std::floor(std::sinf(radians) * maxDistance));
    Vec2i end = Vec2i(endX, endY).toGrid();
    bresenhamLine(start, end, function);
}
} // namespace Line
} // namespace Math
