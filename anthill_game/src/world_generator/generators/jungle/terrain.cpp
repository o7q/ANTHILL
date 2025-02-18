#include "jungle.hpp"

#include <iostream>

void WorldGenerator::JungleGenerator::generate_terrain()
{
    Noise::Perlin perlin(m_settings.seed);

    float scale = 250.0f;

    Particle solid;
    solid.p_mode = Particle::PMode::None;
    solid.p_state = Particle::PState::Solid;
    solid.p_collision_type = Particle::PCollisionType::Solid;

    for (int y = 0; y < m_settings.height; ++y)
    {
        for (int x = 0; x < m_settings.width; ++x)
        {
            float p0 = 0.0f;
            float p0_f = 3.5f;
            float p0_a = 1.0f;
            int p0_i = 1;

            for (int i = 0; i < p0_i; ++i)
            {
                p0 += perlin.sample(x * p0_f / scale, y * p0_f / scale, false) * p0_a;
                p0_f *= 2.0f;
                p0_a /= 1.05f;
            }
            p0 /= p0_i;

            float p1 = 0.0f;
            float p1_f = 2.5f;
            float p1_a = 0.05f;
            int p1_i = 4;

            for (int i = 0; i < p1_i; ++i)
            {
                p1 += perlin.sample(x * p1_f / scale, y * p1_f / scale, true) * p1_a;
                p1_f *= 2.0f;
                p1_a /= 2.f;
            }
            p1 /= p1_i;

            if (p0 > 0.001f)
            {
                Particle dirt = solid;
                float dirt_v = f_rand(0.5f, 1.0f);
                dirt.color = Color(64 * dirt_v, 41 * dirt_v, 5 * dirt_v, 255);

                m_world->setParticle(x, y, dirt, false);

                if (p1 > 0.9f)
                {
                    Particle stone = solid;
                    float stone_v = f_rand(0.7f, 1.0f);
                    stone.color = Color(94 * stone_v, 97 * stone_v, 102 * stone_v, 255);

                    m_world->setParticle(x, y, stone, false);
                }
            }
        }
    }

    std::cout << "done!";
}