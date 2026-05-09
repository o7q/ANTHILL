#pragma once

#include "constants.hpp"
#include "core/math/vec.hpp"
#include <cmath>

struct Angle
{
    Angle() = default;

    float degrees() const { return m_radians * Math::Constants::RAD_TO_DEG; }
    float radians() const { return m_radians; }

  protected:
    float m_radians = 0.0f;
};

struct Degrees : public Angle
{
    Degrees(float degrees) { m_radians = degrees * Math::Constants::DEG_TO_RAD; }
};

struct Radians : public Angle
{
    Radians(float radians) { m_radians = radians; }
};

namespace Math
{
namespace Angles
{
inline Angle vectorsToAngle(Vec2f a, Vec2f b)
{
    Vec2f d = b - a;
    return Radians(std::atan2(d.y, d.x));
}

inline Vec2f rotatePoint(Vec2f origin, Vec2f point, Angle angle)
{
    float radians = angle.radians();

    Vec2f out;

    point -= origin;

    float cosA = std::cosf(radians);
    float sinA = std::sinf(radians);

    out.x = point.x * cosA - point.y * sinA;
    out.y = point.x * sinA + point.y * cosA;

    out += origin;

    return out;
}
} // namespace Angles
} // namespace Math
