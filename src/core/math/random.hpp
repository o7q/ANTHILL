#pragma once

#include "core/math/geometry/vec.hpp"
#include <optional>
#include <random>
#include <vector>

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

inline int seededRandomInt(int min, int max, uint32_t seed)
{
    int range = max - min;
    return hash(range, seed) % range + min;
}

inline uint32_t hashFromPosition(Vec2i pos, uint32_t seed)
{
    uint32_t h = static_cast<uint32_t>(pos.x) ^ (static_cast<uint32_t>(pos.y) << 16);
    return hash(h, seed);
}

// https://dev.to/jacktt/understanding-the-weighted-random-algorithm-581p
template <typename T> struct WeightedValue
{
    T value{};
    int weight = 0;
};
template <typename T>
inline T weightedSelect(const std::vector<WeightedValue<T>> &candidates, std::optional<uint32_t> seed = std::nullopt)
{
    if (candidates.empty())
    {
        return T{};
    }

    int totalWeight = 0;
    for (const WeightedValue<T> &v : candidates)
    {
        totalWeight += v.weight;
    }

    const int random =
        seed.has_value() ? seededRandomInt(0, totalWeight, seed.value()) : unseededRandomInt(0, totalWeight);

    int cursor = 0;
    for (const WeightedValue<T> &v : candidates)
    {
        cursor += v.weight;
        if (cursor > random)
        {
            return v.value;
        }
    }

    return candidates.back().value;
}
} // namespace Random
} // namespace Math
