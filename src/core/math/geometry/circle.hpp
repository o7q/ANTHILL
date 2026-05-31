#pragma once

#include "core/math/geometry/vec.hpp"

template <typename T> struct Circle
{
    Vec2<T> pos;
    T radius{};

    bool pointInside(Vec2<T> point) const { return (point - pos).length() <= radius; }

    template <typename FillFunction> void rasterize(FillFunction &&function)
    {
        int radius_i = static_cast<int>(std::floor(radius));
        for (int ry = -radius_i; ry <= radius_i; ++ry)
        {
            for (int rx = -radius_i; rx <= radius_i; ++rx)
            {
                if (rx * rx + ry * ry <= radius_i * radius_i)
                {
                    function(pos + Vec2i(rx, ry));
                }
            }
        }
    }
};

using Circle_i = Circle<int>;
using Circle_u = Circle<unsigned int>;
using Circle_f = Circle<float>;
using Circle_d = Circle<double>;
