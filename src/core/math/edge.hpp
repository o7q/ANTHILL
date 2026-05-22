#pragma once

#include "core/math/vec.hpp"

template <typename T> struct Edge2
{
    Vec2<T> a;
    Vec2<T> b;

    bool operator==(const Edge2 &other)
    {
        return (a == other.a && b == other.b) || (a == other.b && b == other.a);
    }
};

using Edge2i = Edge2<int>;
using Edge2u = Edge2<unsigned int>;
using Edge2f = Edge2<float>;
using Edge2d = Edge2<double>;
