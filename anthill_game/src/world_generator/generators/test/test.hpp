#pragma once

#include "../generator.hpp"

namespace WorldGenerator
{
    class TestGenerator : public Generator
    {
    public:
        TestGenerator(SDL_Renderer *renderer, Settings settings) : Generator(renderer, settings)
        {
            generate();
        }

    private:
        void generate()
        {
            for (int y = 0; y < m_settings.height; ++y)
            {
                for (int x = 0; x < m_settings.width; ++x)
                {
                    m_world->setParticle(x, y, Particle(Particle::Preset::Stone), false);
                }
            }

            for (int y = 0; y < m_settings.height; ++y)
            {
                for (int x = 0; x < m_settings.width; ++x)
                {
                    if (i_rand(0, 10000) == 0)
                    {
                        m_world->drawParticles(x, y, i_rand(10, 30), Particle(Particle::Preset::Sand), World::DrawShape::Circle, false);
                    }
                    if (i_rand(0, 10000) == 0)
                    {
                        m_world->drawParticles(x, y, i_rand(3, 20), Particle(Particle::Preset::Water), World::DrawShape::Circle, false);
                    }
                    if (i_rand(0, 1000) == 0)
                    {
                        m_world->drawParticles(x, y, i_rand(6, 30), Particle(Particle::Preset::Steam), World::DrawShape::Circle, false);
                    }
                    if (i_rand(0, 100000) == 0)
                    {
                        m_world->drawParticles(x, y, i_rand(20, 30), Particle(Particle::Preset::Blood), World::DrawShape::Circle, false);
                    }
                }
            }
        }
    };
}