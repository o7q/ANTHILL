#pragma once

#include <cmath>

namespace Math
{
namespace Interpolation
{
inline float lerp(float a, float b, float t) { return a + t * (b - a); }

inline float smoothStep(float a, float b, float t)
{
    t = t * t * (3.0f - 2.0f * t);
    return lerp(a, b, t);
}

inline float easeOutCubic(float a, float b, float t)
{
    t = 1.0f - std::pow(1.0f - t, 3.0f);
    return lerp(a, b, t);
}

} // namespace Interpolation
} // namespace Math
