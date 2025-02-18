#include "perlin.hpp"

#include <cmath>

#include "../vector.hpp"
#include "../constants.hpp"

Noise::Perlin::Perlin(unsigned int seed)
{
    m_seed = seed;
}

float Noise::Perlin::sample(float x, float y, bool fast)
{
    int grid_x0 = static_cast<int>(x);
    int grid_y0 = static_cast<int>(y);
    int grid_x1 = grid_x0 + 1;
    int grid_y1 = grid_y0 + 1;

    float weight_x = x - grid_x0;
    float weight_y = y - grid_y0;

    const float dot00 = dot_grid_gradient(grid_x0, grid_y0, x, y, fast);
    const float dot10 = dot_grid_gradient(grid_x1, grid_y0, x, y, fast);
    const float dot01 = dot_grid_gradient(grid_x0, grid_y1, x, y, fast);
    const float dot11 = dot_grid_gradient(grid_x1, grid_y1, x, y, fast);

    const float i_top = interpolate(dot00, dot10, weight_x);
    const float i_bottom = interpolate(dot01, dot11, weight_x);

    return interpolate(i_top, i_bottom, weight_y);
}

Vec2<float> Noise::Perlin::gradient(int grid_x, int grid_y)
{
    unsigned int hash = grid_x * 15514927 ^ grid_y * 57780929 ^ m_seed;
    Vec2<float> gradient(std::cos(hash), std::sin(hash));

    return gradient;
}

Vec2<float> Noise::Perlin::fast_gradient(int grid_x, int grid_y)
{
    unsigned int hash0 = fast_hash(grid_x * 15514927, grid_y * 57780929);
    unsigned int hash1 = fast_hash(grid_x * 20990603, grid_y * 44096281);
    float d = std::sqrt(hash0 * hash0 + hash1 * hash1);

    Vec2<float> gradient(hash0 / d, hash1 / d);

    return gradient;
}

unsigned int Noise::Perlin::fast_hash(int s0, int s1)
{
    unsigned int hash = s0;

    hash ^= (hash >> 16);
    hash *= 0x45d9f3b;

    // Mix in the grid_y
    hash ^= s1;
    hash ^= (hash >> 16);
    hash *= 0x45d9f3b;

    hash ^= m_seed;
    hash ^= (hash << 5) ^ (hash >> 12);

    hash ^= (hash >> 7);

    return hash;
}

float Noise::Perlin::dot_grid_gradient(int grid_x, int grid_y, float sample_x, float sample_y, bool fast)
{
    Vec2<float> g = fast ? fast_gradient(grid_x, grid_y) : gradient(grid_x, grid_y);

    float dx = sample_x - grid_x;
    float dy = sample_y - grid_y;

    return dx * g.x + dy * g.y;
}

float Noise::Perlin::interpolate(float a, float b, float w)
{
    return (b - a) * (3.0f - w * 2.0f) * w * w + a;
}