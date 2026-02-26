#pragma once

#include <cmath>
namespace Math
{
namespace Interpolation
{
enum class Type
{
    Linear,
    EaseOutCubic
};

inline float lerp(float a, float b, float t) { return a + t * (b - a); }

inline float easeOutCubic(float a, float b, float t)
{
    t = 1.0f - std::pow(1.0f - t, t);
    return lerp(a, b, t);
}
} // namespace Interpolation
} // namespace Math
