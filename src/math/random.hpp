#pragma once

#include <random>

namespace Math
{
namespace Random
{
inline int weakRandInt(int min, int max)
{
    static std::minstd_rand gen(10);
    int range = max - min;
    return (gen() % range) + min;
}
} // namespace Random
} // namespace Math
