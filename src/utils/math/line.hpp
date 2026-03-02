#pragma once

#include "backend/types/vec.hpp"
#include <cmath>
#include <optional>

namespace Utils
{
namespace Math
{
namespace Line
{
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
template <typename F>
inline void bresenhamLine(Vec2<int> p1, Vec2<int> p2, F &function)
{
    int dx = std::abs(p2.x - p1.x);
    int dy = -std::abs(p2.y - p1.y);

    int sx = p1.x < p2.x ? 1 : -1;
    int sy = p1.y < p2.y ? 1 : -1;

    int error = dx + dy;

    while (true)
    {
        if (function(p1.x, p1.y))
        {
            break;
        }

        int e2 = 2 * error;
        if (e2 >= dy)
        {
            if (p1.x == p2.x)
            {
                break;
            }
            error = error + dy;
            p1.x = p1.x + sx;
        }
        if (e2 <= dx)
        {
            if (p1.y == p2.y)
            {
                break;
            }

            error = error + dx;
            p1.y = p1.y + sy;
        }
    }
}

// https://www.youtube.com/watch?v=NbSee-XM7WA
template <typename F>
inline std::optional<Vec2<float>>
ddaRaycast(Vec2<float> rayStart, Vec2<float> rayDirection, F &checkFunction)
{
    float a = rayDirection.y / rayDirection.x;
    float b = rayDirection.x / rayDirection.y;
    Vec2<float> rayUnitStepSize = {std::sqrt(1.0f + a * a),
                                   std::sqrt(1.0f + b * b)};

    Vec2<int> gridCheck = rayStart.toGrid();
    Vec2<float> rayLength1D;

    Vec2<float> step;
    if (rayDirection.x < 0)
    {
        step.x = -1;
        rayLength1D.x =
            (rayStart.x - static_cast<float>(gridCheck.x)) * rayUnitStepSize.x;
    }
    else
    {
        step.x = 1;
        rayLength1D.x = (static_cast<float>(gridCheck.x + 1) - rayStart.x) *
                        rayUnitStepSize.x;
    }

    if (rayDirection.y < 0)
    {
        step.y = -1;
        rayLength1D.y =
            (rayStart.y - static_cast<float>(gridCheck.y)) * rayUnitStepSize.y;
    }
    else
    {
        step.y = 1;
        rayLength1D.y = (static_cast<float>(gridCheck.y + 1) - rayStart.y) *
                        rayUnitStepSize.y;
    }

    float distance = 0.0f;
    while (true)
    {
        if (rayLength1D.x < rayLength1D.y)
        {
            gridCheck.x += step.x;
            distance = rayLength1D.x;
            rayLength1D.x += rayUnitStepSize.x;
        }
        else
        {
            gridCheck.y += step.y;
            distance = rayLength1D.y;
            rayLength1D.y += rayUnitStepSize.y;
        }

        if (checkFunction(gridCheck.x, gridCheck.y))
        {
            return rayStart + rayDirection * distance;
        }
    }

    return std::nullopt;
}
} // namespace Line
} // namespace Math
} // namespace Utils
