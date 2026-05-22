#pragma once

#include "core/math/geometry/vec.hpp"

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
