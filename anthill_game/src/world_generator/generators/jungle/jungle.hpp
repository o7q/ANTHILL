#pragma once

#include <algorithm>

#include "../generator.hpp"

#include "../../../engine/math/noise/perlin.hpp"

namespace WorldGenerator
{
    class JungleGenerator : public Generator
    {
    public:
        JungleGenerator(Settings settings) : Generator(settings)
        {
            generate();
        }

    private:
        void generate()
        {
            Noise::Perlin perlin(m_settings.seed);

            float frequency = 5.0f;

            for (int y = 0; y < m_settings.height; ++y)
            {
                for (int x = 0; x < m_settings.width; ++x)
                {
                    float p = perlin.sample(x * frequency / static_cast<float>(m_settings.width), y * frequency / static_cast<float>(m_settings.height));
                    int value = std::clamp(p * 1000, 0.0f, 255.0f);

                    if (value > 250.0f)
                    {
                        m_world->setParticle(x, y, Particle(Particle::Preset::Sand), false);
                    }
                    else if (value % 3 == 0)
                    {
                        m_world->setParticle(x, y, Particle(Particle::Preset::Stone), false);
                    } else
                    {
                        m_world->setParticle(x, y, Particle(Particle::Preset::Blood), false);
                    }
                }
            }
        }
    };
}