#pragma once

#include "vector.hpp"

struct Segment
{
    Segment() = default;
    Segment(Vec2<float> a, Vec2<float> b) : a(a), b(b) {}
    Segment(float x1, float y1, float x2, float y2) : a(x1, y1), b(x2, y2) {}

    Vec2<float> a, b;
};