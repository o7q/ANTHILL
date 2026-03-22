#pragma once

#include "constants.hpp"
#include "math/vec.hpp"
#include <cmath>

namespace Math
{
namespace Angle
{
inline float degreesToRadians(float degrees)
{
    return static_cast<float>(Constants::DEG_TO_RAD) * degrees;
}
inline float radiansToDegrees(float radians)
{
    return static_cast<float>(Constants::RAD_TO_DEG) * radians;
}
inline float vectorsToAngle(Vec2f a, Vec2f b)
{
    Vec2f d = b - a;
    return std::atan2(d.y, d.x);
}
inline Vec2f rotatePoint(Vec2f origin, Vec2f point, float angle)
{
    Vec2f out;

    point -= origin;

    float cosA = std::cosf(angle);
    float sinA = std::sinf(angle);

    out.x = point.x * cosA - point.y * sinA;
    out.y = point.x * sinA + point.y * cosA;

    out += origin;

    return out;
}
} // namespace Angle
} // namespace Math
