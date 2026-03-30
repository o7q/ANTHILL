#pragma once

#include "math/perlin.hpp"
#include "math/random.hpp"
#include "utils/data.hpp"
#include "utils/data_structures/index_2d.hpp"
#include "world/particle/particle_world.hpp"

class Generator
{
  public:
    Generator(ParticleWorld &world) : r_world(world)
    {
        m_seed = Math::Random::weakRandInt(0, 10000);
    }

    void generateInRadius(Vec2i origin, Vec2i size)
    {
        Index2D chunkOrigin = r_world.getParticles().getChunkIndex(origin);
        if (Utils::Data::doesVectorContain(m_origins, chunkOrigin))
        {
            return;
        }

        m_origins.push_back(chunkOrigin);
        Vec2i halfSize = size / 2;
        Vec2u chunkSize = r_world.getParticles().getChunkSize();

        for (int cy = chunkOrigin.y - halfSize.y;
             cy <= chunkOrigin.y + halfSize.y; ++cy)
        {
            for (int cx = chunkOrigin.x - halfSize.x;
                 cx <= chunkOrigin.x + halfSize.x; ++cx)
            {
                if (r_world.getParticles().hasChunk(Index2D(cx, cy)))
                {
                    continue;
                }

                for (unsigned int y = 0; y < chunkSize.y; ++y)
                {
                    for (unsigned int x = 0; x < chunkSize.x; ++x)
                    {
                        int ax = cx * chunkSize.x + x;
                        int ay = cy * chunkSize.y + y;

                        float v = Math::Perlin::sampleEx(Vec2f(ax, ay),
                                                         {300, 200}, 5, m_seed);

                        if (v > 0.1f)
                        {
                            float v2 = Math::Perlin::sampleEx(
                                Vec2f(ax, ay), {500, 500}, 10, m_seed);
                            Particle p;
                            if (v2 >= 0.2f)
                            {
                                float v3 = Math::Perlin::sampleEx(
                                    Vec2f(ax, ay), {50, 50}, 10, m_seed);

                                if (v3 >= 0.4f)
                                {
                                    p.setColor(Color(219, 167, 88));
                                    p.setPhysicsType(
                                        Particle::PhysicsType::Water);
                                    p.setMatterType(
                                        Particle::MatterType::Liquid);
                                    p.setRestitution(0.3f);
                                }
                                else
                                {
                                    p.setColor(Color(120, 114, 107));
                                    p.setPhysicsType(
                                        Particle::PhysicsType::None);
                                    p.setMatterType(
                                        Particle::MatterType::Solid);
                                    p.getVerlet().setMass(200000000);
                                    p.setImmovable(true);
                                }
                            }
                            else
                            {
                                p.setColor(Color(138, 138, 138));
                                p.setPhysicsType(Particle::PhysicsType::None);
                                p.setMatterType(Particle::MatterType::Solid);
                                p.getVerlet().setMass(200000000);
                                p.setImmovable(true);
                            }
                            r_world.getEditor().set({ax, ay}, p);
                        }
                    }
                }
            }
        }
    }

  private:
    ParticleWorld &r_world;
    std::vector<Index2D> m_origins;

    int m_seed = 0;
};
