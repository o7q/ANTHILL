#pragma once

#include "core/math/triangle.hpp"
#include "core/math/vec.hpp"
#include <vector>

inline std::vector<Triangle2f> generateDelaunayTriangle(const std::vector<Vec2f> &points)
{
    std::vector<Triangle2f> out;

    Triangle2f superTriangle;
    superTriangle.setVertices({10, 10}, {240, 10}, {120, 200});

    out.push_back(superTriangle);
    return out;
}
