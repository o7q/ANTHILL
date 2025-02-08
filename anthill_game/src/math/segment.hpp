#pragma once

#include "vector.hpp"

struct Segment
{
    struct SCollision
    {
        bool is_colliding = false;

        float intersection_x = 0.0f;
        float intersection_y = 0.0f;

        float range_a = 0.0f;
        float range_b = 0.0f;
    };

    Segment() = default;
    Segment(Vec2<float> a, Vec2<float> b) : a(a), b(b) {}
    Segment(float x1, float y1, float x2, float y2) : a(x1, y1), b(x2, y2) {}

    const SCollision colliding(const Segment &other) const
    {
        float x1 = a.x;
        float x2 = b.x;
        float x3 = other.a.x;
        float x4 = other.b.x;

        float y1 = a.y;
        float y2 = b.y;
        float y3 = other.a.y;
        float y4 = other.b.y;

        float d  =  (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
        float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
        float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / d;

        SCollision s_collision;
        if (uA >= 0.0f && uA <= 1.0f && uB >= 0 && uB <= 1.0f)
        {
            s_collision.is_colliding = true;

            float intersection_x = x1 + uA * (x2 - x1);
            float intersection_y = y1 + uA * (y2 - y1);

            s_collision.intersection_x = intersection_x;
            s_collision.intersection_y = intersection_y;

            s_collision.range_a = uA;
            s_collision.range_b = uB;
        }

        return s_collision;
    }

    Vec2<float> a, b;
};