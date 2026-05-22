#pragma once

#include "core/math/geometry/vec.hpp"

template <typename T> struct Segment
{
    Vec2<T> a;
    Vec2<T> b;

    bool operator==(const Segment &other)
    {
        return (a == other.a && b == other.b) || (a == other.b && b == other.a);
    }
};

using Segment_i = Segment<int>;
using Segment_u = Segment<unsigned int>;
using Segment_f = Segment<float>;
using Segment_d = Segment<double>;
