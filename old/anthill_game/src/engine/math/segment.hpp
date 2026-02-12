#pragma once

#include "vector.hpp"

struct Segment
{
    struct IData
    {
        bool intersecting = false;

        Vec2<float> position;

        float range_a = 0.0f;
        float range_b = 0.0f;
    };

    Segment() = default;
    Segment(Vec2<float> a, Vec2<float> b) : a(a), b(b) {}
    Segment(float x1, float y1, float x2, float y2) : a(x1, y1), b(x2, y2) {}

    const IData segmentIntersect(const Segment &other) const;

    Vec2<float> a, b;
};