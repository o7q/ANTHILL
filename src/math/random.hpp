#pragma once

#include "math/vec.hpp"
#include <random>

namespace Math
{
namespace Random
{
inline int unseededRandomInt(int min, int max)
{
    static std::minstd_rand gen(std::random_device{}());
    int range = max - min;
    return (gen() % range) + min;
}

// https://en.wikipedia.org/wiki/MurmurHash
inline uint32_t hash(uint32_t v, uint32_t seed)
{
    v ^= seed;
    v ^= v >> 16;
    v *= 0x85ebca6b;
    v ^= v >> 13;
    v *= 0xc2b2ae35;
    v ^= v >> 16;
    return v;
}

inline uint32_t hashFromPosition(Vec2i pos, uint32_t seed)
{
    uint32_t h =
        static_cast<uint32_t>(pos.x) ^ (static_cast<uint32_t>(pos.y) << 16);
    return hash(h, seed);
}
} // namespace Random
} // namespace Math
