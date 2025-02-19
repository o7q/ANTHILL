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
            PerlinSampler terrain(perlin);
            terrain.setXScale(180.0f);
            terrain.setYScale(160.0f);
            terrain.setIterations(4);

            if (terrain.sample(x, y) >= 0.44f)
            {
                Particle p = solid;
                float r = f_rand(0.85f, 1.0f);
                p.color = Color(24 * r, 38 * r, 21 * r, 255);
                m_world->setParticle(x, y, p, false);

                terrain.setXScale(180.0f);
                terrain.setYScale(160.0f);
                terrain.setIterations(8);

                if (terrain.sample(x, y) >= 0.50f)
                {
                    p.color = Color(40 * r, 30 * r, 11 * r, 255);
                    m_world->setParticle(x, y, p, false);

                    if (terrain.sample(x, y) >= 0.6f)
                    {
                        p.color = Color(55 * r, 55 * r, 55 * r, 255);
                        m_world->setParticle(x, y, p, false);

                        if (terrain.sample(x, y) >= 0.63f)
                        {
                            p.color = Color(80 * r, 80 * r, 80 * r, 255);
                            m_world->setParticle(x, y, p, false);
                        }
                    }
                }
            }
        }
    }
}