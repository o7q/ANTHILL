#pragma once

#include "backend/types/vec.hpp"
#include <cmath>
#include <optional>

namespace Math
{
// https://www.youtube.com/watch?v=NbSee-XM7WA
template <typename F>
inline std::optional<Vec2<float>>
ddaRaycast(Vec2<float> rayStart, Vec2<float> rayDirection, F &checkFunction)
{
    float a = rayDirection.y / rayDirection.x;
    float b = rayDirection.x / rayDirection.y;
    Vec2<float> rayUnitStepSize = {std::sqrt(1.0f + a * a),
                                   std::sqrt(1.0f + b * b)};

    Vec2<int> gridCheck = rayStart;
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
} // namespace Math
