#pragma once

#include "core/math/vec.hpp"

template <typename T> struct Edge
{
    Vec2<T> a;
    Vec2<T> b;

    bool operator==(const Edge &other)
    {
        return (a == other.a && b == other.b) || (a == other.b && b == other.a);
    }
};

using Edge2i = Edge<int>;
using Edge2u = Edge<unsigned int>;
using Edge2f = Edge<float>;
using Edge2d = Edge<double>;
