#pragma once

#include <random>

namespace Random
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    inline void seed()
    {
        gen.seed(rd());
    }

    inline int genInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max - 1);
        return dist(gen);
    }

    inline float genFloat(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(gen);
    }
}