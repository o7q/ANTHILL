#include "generator.hpp"

WorldGenerator::Generator::Generator(SDL_Renderer *renderer, Settings settings)
{
    m_world = new World(renderer, settings.width, settings.height);

    if (settings.seed < 0)
    {
        settings.seed = Random::genInt(0, std::numeric_limits<int>::max());
    }

    m_gen = std::mt19937(settings.seed);
    m_settings = settings;
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