#pragma once

#include "core/math/geometry/vec.hpp"

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
