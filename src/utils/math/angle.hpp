#pragma once

#include "backend/utils/vec.hpp"
#include "utils/math/constants.hpp"
#include <cmath>

namespace Utils
{
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
inline float vectorsToAngle(Vec2<float> a, Vec2<float> b)
{
    Vec2<float> d = b - a;
    return std::atan2(d.y, d.x);
}
inline Vec2<float> rotatePoint(Vec2<float> origin, Vec2<float> point,
                               float angle)
{
    Vec2<float> out;

    point -= origin;

    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    out.x = point.x * cosA - point.y * sinA;
    out.y = point.x * sinA + point.y * cosA;

    out += origin;

    return out;
}
} // namespace Angle
} // namespace Math
} // namespace Utils
