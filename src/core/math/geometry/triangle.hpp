#pragma once

#include "core/math/geometry/circle.hpp"
#include "core/math/geometry/segment.hpp"
#include "core/math/geometry/vec.hpp"
#include <cmath>
#include <vector>

template <typename T> struct Triangle2
{
    bool operator==(const Triangle2 &other)
    {
        int matches = 0;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (verts[i] == other.verts[j])
                {
                    matches++;
                    break;
                }
            }
        }
        return matches == 3;
    }

    Circle2f generateCircumcircle()
    {
        // https://en.wikipedia.org/wiki/Circumcircle#Cartesian_coordinates_2
        Vec2i a = verts[0];
        Vec2i b = verts[1];
        Vec2i c = verts[2];

        int axsq = a.x * a.x;
        int aysq = a.y * a.y;
        int bxsq = b.x * b.x;
        int bysq = b.y * b.y;
        int cxsq = c.x * c.x;
        int cysq = c.y * c.y;

        float d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        float x =
            ((axsq + aysq) * (b.y - c.y) + (bxsq + bysq) * (c.y - a.y) + (cxsq + cysq) * (a.y - b.y)) / d;
        float y =
            ((axsq + aysq) * (c.x - b.x) + (bxsq + bysq) * (a.x - c.x) + (cxsq + cysq) * (b.x - a.x)) / d;

        float dx = x - a.x;
        float dy = y - a.y;
        float r  = std::sqrt(dx * dx + dy * dy);

        Circle2f out;
        out.pos    = {x, y};
        out.radius = r;
        return out;
    }

    std::vector<Segment2<T>> generateSegments() const
    {
        std::vector<Segment2<T>> segments;
        segments.push_back({verts[0], verts[1]});
        segments.push_back({verts[1], verts[2]});
        segments.push_back({verts[2], verts[0]});
        return segments;
    }

    Vec2<T> verts[3];
};

using Triangle2i = Triangle2<int>;
using Triangle2u = Triangle2<unsigned int>;
using Triangle2f = Triangle2<float>;
using Triangle2d = Triangle2<double>;
