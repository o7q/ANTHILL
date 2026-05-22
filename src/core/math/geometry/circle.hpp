#pragma once

#include "core/math/geometry/vec.hpp"

template <typename T> struct Circle
{
    Vec2<T> pos;
    T radius{};

    bool pointInside(Vec2<T> point) const { return (point - pos).length() <= radius; }
};

using Circle_i = Circle<int>;
using Circle_u = Circle<unsigned int>;
using Circle_f = Circle<float>;
using Circle_d = Circle<double>;
