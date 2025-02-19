#include "jungle.hpp"

#include <algorithm>

void WorldGenerator::JungleGenerator::generate_terrain()
{
    PerlinNoise perlin(m_settings.seed);

    Particle solid;
    solid.p_mode = Particle::PMode::None;
    solid.p_state = Particle::PState::Solid;
    solid.p_collision_type = Particle::PCollisionType::Solid;

    for (int y = 0; y < m_settings.height; ++y)
    {
        for (int x = 0; x < m_settings.width; ++x)
        {
            PerlinSampler sampler(perlin);
            sampler.setXScale(180.0f);
            sampler.setYScale(160.0f);
            sampler.setIterations(4);

            PerlinSampler sampler2(perlin);
            sampler2.setXScale(180.0f);
            sampler2.setYScale(159.0f);
            sampler2.setIterations(4);

            if ((sampler2.sample(x, y) >= 0.46f))
            {
                Particle p_water(Particle::Preset::Water);
                p_water.color = Color(48, 159, 171, 230);
                m_world->setParticle(x, y, p_water, false);
            }

            if (!(sampler.sample(x, y) >= 0.44f))
            {
                continue;
            }

            // grass
            Particle p = solid;
            float r = f_rand(0.9f, 1.0f);
            p.color = Color(102 * r, 146 * r, 56 * r, 255);
            m_world->setParticle(x, y, p, false);

            // water
            if (sampler.sample(x, y) >= 0.46f)
            {
                Particle p_water(Particle::Preset::Water);
                p_water.color = Color(48, 159, 171, 230);
                m_world->setParticle(x, y, p_water, false);
            }

            sampler.setXScale(180.0f);
            sampler.setYScale(160.0f);
            sampler.setIterations(6);

            if (!(sampler.sample(x, y) >= 0.47f))
            {
                continue;
            }

            // grass 2
            p.color = Color(80 * r, 93 * r, 40 * r, 255);
            m_world->setParticle(x, y, p, false);

            if (!(sampler.sample(x, y) >= 0.515f))
            {
                continue;
            }

            // dirt
            r = f_rand(0.7f, 1.0f);
            p.color = Color(40 * r, 30 * r, 11 * r, 255);
            m_world->setParticle(x, y, p, false);
            if (f_rand(0.0f, 1.0f) > 0.7f)
            {
                p.color = Color(45 * r, 32 * r, 21 * r, 255);
                m_world->setParticle(x, y, p, false);
            }
            if (f_rand(0.0f, 1.0f) > 0.99f)
            {
                p.color = Color(48 * r, 42 * r, 44 * r, 255);
                m_world->setParticle(x, y, p, false);
            }
            if (f_rand(0.0f, 1.0f) > 0.999f)
            {
                p.color = Color(96 * r, 95 * r, 88 * r, 255);
                m_world->setParticle(x, y, p, false);
            }

            if (!(sampler.sample(x, y) >= 0.6f))
            {
                continue;
            }

            // stone
            r = f_rand(0.9f, 1.0f);
            p.color = Color(133 * r, 122 * r, 97 * r, 255);
            m_world->setParticle(x, y, p, false);

            if (!(sampler.sample(x, y) >= 0.63f))
            {
                continue;
            }

            // stone 2
            p.color = Color(155 * r, 162 * r, 146 * r, 255);
            m_world->setParticle(x, y, p, false);

            if (!(sampler.sample(x, y) >= 0.69f))
            {
                continue;
            }

            // stone 3
            p.color = Color(130 * r, 129 * r, 130 * r, 255);
            m_world->setParticle(x, y, p, false);
        }
    }
}