#include "generator.hpp"

#include <algorithm>

float WorldGenerator::Generator::PerlinSampler::sample(int x, int y)
{
    float v = 0.0f;

    float f = 1.0f;
    float a = 1.0f;

    for (int i = 0; i < m_iterations; ++i)
    {
        v += m_noise.sample(x * f / m_scale_x, y * f / m_scale_y) * a;
        f *= 2.0f;
        a /= 2.0f;
    }

    v = std::clamp(v, -1.0f, 1.0f);
    v = (v + 1.0f) / 2.0f;

    return v;
}

void WorldGenerator::Generator::PerlinSampler::setXScale(float scale_x)
{
    m_scale_x = scale_x;
}
void WorldGenerator::Generator::PerlinSampler::setYScale(float scale_y)
{
    m_scale_y = scale_y;
}

void WorldGenerator::Generator::PerlinSampler::setIterations(int iterations)
{
    m_iterations = iterations;
}