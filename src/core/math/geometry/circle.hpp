#pragma once

#include "core/math/geometry/vec.hpp"

template <typename T> struct Circle2
{
    Vec2<T> pos;
    T radius{};

    bool pointInside(Vec2<T> point) const { return (point - pos).length() <= radius; }
};

using Circle2i = Circle2<int>;
using Circle2u = Circle2<unsigned int>;
using Circle2f = Circle2<float>;
using Circle2d = Circle2<double>;
