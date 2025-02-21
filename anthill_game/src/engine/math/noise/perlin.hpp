#pragma once

#include "../vector.hpp"

class PerlinNoise
{

public:
    PerlinNoise(unsigned int seed);
    float sample(float x, float y);

private:
    Vec2<float> gradient(int grid_x, int grid_y);
    float dot_grid_gradient(int grid_x, int grid_y, float sample_x, float sample_y);
    float interpolate(float a, float b, float weight);

private:
    unsigned int m_seed;
};