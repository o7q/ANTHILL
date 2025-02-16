#pragma once

#include <SDL3/SDL.h>

#include <limits>

#include "../world/world.hpp"
#include "../engine/math/random.hpp"

class WorldGenerator
{
public:
    struct Settings
    {
        int width = 0;
        int height = 0;

        int seed = -1;
    };

public:
    WorldGenerator(SDL_Renderer *renderer, Settings settings)
    {
        if (settings.seed < 0)
        {
            settings.seed = Random::genInt(0, std::numeric_limits<unsigned int>::max());
        }

        m_settings = settings;

        m_gen = std::mt19937(settings.seed);
        m_world = new World(renderer, settings.width, settings.height);
    }

    World *world()
    {
        return m_world;
    }

protected:
    int i_rand(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max - 1);
        return dist(m_gen);
    }

    float f_rand(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(m_gen);
    }

protected:
    Settings m_settings;

    World *m_world = nullptr;

private:
    std::mt19937 m_gen;
};