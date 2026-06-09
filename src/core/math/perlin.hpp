#pragma once

#include "core/math/geometry/vec.hpp"
#include "core/math/interpolation.hpp"
#include "core/math/random.hpp"
#include <algorithm>
#include <array>
#include <cstdint>

namespace Math
{
namespace Perlin
{
inline static const std::array<Vec2f, 16> gradients = {
    Vec2f{1.0000f, 0.0000f},   Vec2f{0.9239f, 0.3827f},   Vec2f{0.7071f, 0.7071f},
    Vec2f{0.3827f, 0.9239f},   Vec2f{-0.0000f, 1.0000f},  Vec2f{-0.3827f, 0.9239f},
    Vec2f{-0.7071f, 0.7071f},  Vec2f{-0.9239f, 0.3827f},  Vec2f{-1.0000f, -0.0000f},
    Vec2f{-0.9239f, -0.3827f}, Vec2f{-0.7071f, -0.7071f}, Vec2f{-0.3827f, -0.9239f},
    Vec2f{0.0000f, -1.0000f},  Vec2f{0.3827f, -0.9239f},  Vec2f{0.7071f, -0.7071f},
    Vec2f{0.9239f, -0.3827f},
};

inline Vec2f randomGradient(Vec2i index, uint32_t seed)
{
    uint32_t h = Random::hashFromPosition(index, seed);
    return gradients[h >> 28];
}

inline float sample(Vec2f pos, uint32_t seed)
{
    int x_int = static_cast<int>(std::floor(pos.x));
    int y_int = static_cast<int>(std::floor(pos.y));

    Vec2i corner0 = Vec2i(x_int, y_int);
    Vec2i corner1 = Vec2i(x_int + 1, y_int);
    Vec2i corner2 = Vec2i(x_int, y_int + 1);
    Vec2i corner3 = Vec2i(x_int + 1, y_int + 1);

    Vec2f localPos = pos - corner0.toFloat();

    Vec2f gradient0 = randomGradient(corner0, seed);
    Vec2f gradient1 = randomGradient(corner1, seed);
    Vec2f gradient2 = randomGradient(corner2, seed);
    Vec2f gradient3 = randomGradient(corner3, seed);

    Vec2f inwardsGradient0 = localPos;
    Vec2f inwardsGradient1 = localPos - Vec2f(1.0f, 0.0f);
    Vec2f inwardsGradient2 = localPos - Vec2f(0.0f, 1.0f);
    Vec2f inwardsGradient3 = localPos - Vec2f(1.0f, 1.0f);

    float dot0 = gradient0.dot(inwardsGradient0);
    float dot1 = gradient1.dot(inwardsGradient1);
    float dot2 = gradient2.dot(inwardsGradient2);
    float dot3 = gradient3.dot(inwardsGradient3);

    float interp0 = Math::Interpolation::smoothStep(dot0, dot1, localPos.x);
    float interp1 = Math::Interpolation::smoothStep(dot2, dot3, localPos.x);
    return Math::Interpolation::smoothStep(interp0, interp1, localPos.y);
}

inline float sampleEx(Vec2f pos, Vec2f gridSize, int iterations, uint32_t seed)
{
    float v = 0.0f;
    float f = 1.0f;
    float a = 1.0f;
    for (int i = 0; i < iterations; ++i)
    {
        v += sample(pos * f / gridSize, seed) * a;
        f *= 2.0f;
        a /= 2.0f;
    }

    return std::clamp(v + 0.5f, 0.0f, 1.0f);
}
} // namespace Perlin
} // namespace Math
