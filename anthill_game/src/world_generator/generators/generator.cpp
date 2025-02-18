#include "generator.hpp"

WorldGenerator::Generator::Generator(Settings settings)
{
    m_world = new World(settings.width, settings.height);
    m_settings = settings;
    m_gen = std::mt19937(settings.seed);
}

World *WorldGenerator::Generator::world()
{
    return m_world;
}

int WorldGenerator::Generator::i_rand(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max - 1);
    return dist(m_gen);
}

float WorldGenerator::Generator::f_rand(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_gen);
}