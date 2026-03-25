#pragma once

#include "math/perlin.hpp"
#include "utils/data_structures/index_2d.hpp"
#include "world/particle/particle_handler.hpp"
class Generator
{
  public:
    Generator(ParticleHandler &particles) : r_particles(particles) {}

    void generateInRadius(int x, int y, int radius)
    {
        Index2D chunkIndex = r_particles.getParticles().getChunkIndex(x, y);
        Vec2u chunkSize = r_particles.getParticles().getChunkSize();
        for (int y = -radius; y <= radius; ++y)
        {
            for (int x = -radius; x <= radius; ++x)
            {
                int cx = chunkIndex.x + x;
                int cy = chunkIndex.y + y;

                int dx = chunkIndex.x - cx;
                int dy = chunkIndex.y - cy;

                if (dx * dx + dy * dy > radius * radius)
                {
                    continue;
                }

                if (r_particles.getParticles().hasChunk(Index2D(cx, cy)))
                {
                    continue;
                }

                for (unsigned int y = 0; y < chunkSize.y; ++y)
                {
                    for (unsigned int x = 0; x < chunkSize.x; ++x)
                    {
                        int ax = cx * chunkSize.x + x;
                        int ay = cy * chunkSize.y + y;

                        float v = Math::Perlin::sampleEx(ax, ay, 200, 4, 0);

                        if (v > 0.01f)
                        {
                            Particle p;
                            p.setColor(Color(200, 205, 200));
                            p.setPhysicsType(Particle::PhysicsType::None);
                            p.setMatterType(Particle::MatterType::Solid);
                            p.getVerlet().setMass(200000000);
                            p.setImmovable(true);

                            r_particles.getParticles().set(ax, ay, p);
                        }
                    }
                }
            }
        }
    }

  private:
    ParticleHandler &r_particles;
};
