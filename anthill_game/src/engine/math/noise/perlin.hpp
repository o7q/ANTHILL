#pragma once

#include "../vector.hpp"

namespace Noise
{
    class Perlin
    {

    public:
        Perlin(unsigned int seed);
        float sample(float x, float y, bool fast);

    private:
        float dot_grid_gradient(int grid_x, int grid_y, float sample_x, float sample_y, bool fast);

        Vec2<float> gradient(int grid_x, int grid_y);
        Vec2<float> fast_gradient(int grid_x, int grid_y);

        float interpolate(float a, float b, float weight);

        unsigned int fast_hash(int s0, int s1);

    private:
        unsigned int m_seed = 0;
    };
}