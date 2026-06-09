#pragma once

#include "core/math/geometry/circle.hpp"
#include "core/math/geometry/segment.hpp"
#include "core/math/geometry/vec.hpp"
#include <cmath>
#include <vector>

template <typename T> struct Triangle
{
    bool operator==(const Triangle &other)
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

    Circle_d generateCircumcircle()
    {
        // https://en.wikipedia.org/wiki/Circumcircle#Cartesian_coordinates_2
        Vec2d a = verts[0].toDouble();
        Vec2d b = verts[1].toDouble();
        Vec2d c = verts[2].toDouble();

        double axsq = a.x * a.x;
        double aysq = a.y * a.y;
        double bxsq = b.x * b.x;
        double bysq = b.y * b.y;
        double cxsq = c.x * c.x;
        double cysq = c.y * c.y;

        double d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        double x =
            ((axsq + aysq) * (b.y - c.y) + (bxsq + bysq) * (c.y - a.y) + (cxsq + cysq) * (a.y - b.y)) / d;
        double y =
            ((axsq + aysq) * (c.x - b.x) + (bxsq + bysq) * (a.x - c.x) + (cxsq + cysq) * (b.x - a.x)) / d;

        double dx = x - a.x;
        double dy = y - a.y;
        double r  = std::sqrt(dx * dx + dy * dy);

        Circle_d out;
        out.pos    = Vec2d{x, y};
        out.radius = r;
        return out;
    }

    std::vector<Segment<T>> generateSegments() const
    {
        std::vector<Segment<T>> segments;
        segments.push_back({verts[0], verts[1]});
        segments.push_back({verts[1], verts[2]});
        segments.push_back({verts[2], verts[0]});
        return segments;
    }

    Vec2<T> verts[3];
};

using Triangle_i = Triangle<int>;
using Triangle_u = Triangle<unsigned int>;
using Triangle_f = Triangle<float>;
using Triangle_d = Triangle<double>;
