#pragma once

#include "math/vec.hpp"
#include <cmath>

namespace Math
{
namespace Distance
{
inline float euclidian(Vec2f a, Vec2f b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

inline float manhattan(Vec2f a, Vec2f b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::abs(dx) + std::abs(dy);
}
} // namespace Distance
} // namespace Math
