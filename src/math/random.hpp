#pragma once

#include "math/vec.hpp"
#include <random>

namespace Math
{
namespace Random
{
inline int weakRandInt(int min, int max)
{
    static std::minstd_rand gen(std::random_device{}());
    int range = max - min;
    return (gen() % range) + min;
}

// https://en.wikipedia.org/wiki/MurmurHash
inline uint32_t hashFromPosition(Vec2i pos, uint32_t seed = 0)
{
    uint32_t h = (uint32_t)pos.x ^ ((uint32_t)pos.y << 16);
    h ^= seed;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}
} // namespace Random
} // namespace Math
