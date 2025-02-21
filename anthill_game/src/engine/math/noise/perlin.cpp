#include "perlin.hpp"

#include <cmath>

#include "../vector.hpp"
#include "../constants.hpp"

PerlinNoise::PerlinNoise(unsigned int seed)
{
    m_seed = seed;
}

float PerlinNoise::sample(float x, float y)
{
    int grid_x0 = static_cast<int>(x);
    int grid_y0 = static_cast<int>(y);
    int grid_x1 = grid_x0 + 1;
    int grid_y1 = grid_y0 + 1;

    float weight_x = x - grid_x0;
    float weight_y = y - grid_y0;

    const float dot00 = dot_grid_gradient(grid_x0, grid_y0, x, y);
    const float dot10 = dot_grid_gradient(grid_x1, grid_y0, x, y);
    const float dot01 = dot_grid_gradient(grid_x0, grid_y1, x, y);
    const float dot11 = dot_grid_gradient(grid_x1, grid_y1, x, y);

    const float i_top    = interpolate(dot00, dot10, weight_x);
    const float i_bottom = interpolate(dot01, dot11, weight_x);

    return interpolate(i_top, i_bottom, weight_y);
}

Vec2<float> PerlinNoise::gradient(int grid_x, int grid_y)
{
    unsigned int hash = grid_x * 15514927 ^ grid_y * 57780929 ^ m_seed;
    int angle = hash % 360;

    return Vec2<float>(fastCos(angle), fastSin(angle));
}

float PerlinNoise::dot_grid_gradient(int grid_x, int grid_y, float sample_x, float sample_y)
{
    Vec2<float> g = gradient(grid_x, grid_y);

    float dx = sample_x - grid_x;
    float dy = sample_y - grid_y;

    return dx * g.x + dy * g.y;
}

float PerlinNoise::interpolate(float a, float b, float w)
{
    return (b - a) * (3.0f - w * 2.0f) * w * w + a;
}