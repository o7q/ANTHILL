#pragma once

#include "engine/sparse_chunk_map.hpp"
#include "engine/world/particle.hpp"
#include "engine/world/particle_dynamics/p_dynamics_handler.hpp"

class ParticleHandler
{
  public:
    ParticleHandler() : m_particles(32, 32), m_pDynamicsHandler(m_particles) {}

    void update(float dt) { m_pDynamicsHandler.update(dt); }
    void set(int x, int y, Particle p)
    {
        p.getVerlet().setPosition(x, y);
        m_particles.set(x, y, p);
    }

    void draw(int x, int y, Particle p, int radius = 5)
    {
        for (int ry = -radius; ry <= radius; ++ry)
        {
            for (int rx = -radius; rx <= radius; ++rx)
            {
                if (rx * rx + ry * ry <= radius * radius)
                {
                    set(x + rx, y + ry, p);
                }
            }
        }
    }

    void applyForce(float x, float y, float power)
    {
        for (auto &[chunkPos, chunk] : m_particles.getChunks())
        {
            Vec2<unsigned int> chunkSize = m_particles.getChunkSize();
            for (unsigned int cy = 0; cy < chunkSize.y; ++cy)
            {
                for (unsigned int cx = 0; cx < chunkSize.x; ++cx)
                {
                    const int px = chunkPos.first * chunkSize.x + cx;
                    const int py = chunkPos.second * chunkSize.y + cy;
                    Particle *p = m_particles.get(px, py);

                    if (!p)
                    {
                        continue;
                    }

                    if (p->isAir())
                    {
                        continue;
                    }

                    Vec2<float> dir =
                        Vec2<float>(x, y) - p->getVerlet().getPosition();

                    dir = dir.negate();

                    float distance = dir.length();

                    if (distance > 0.001f)
                    {
                        dir = dir / distance;
                    }

                    float strength = power;
                    Vec2<float> force = dir * strength;

                    p->getVerlet().addForce(force.x, force.y);
                }
            }
        }
    }

    SparseChunkMap<Particle> &getParticles() { return m_particles; }
    PDynamicsHandler &getDynamics() { return m_pDynamicsHandler; }

  private:
    SparseChunkMap<Particle> m_particles;
    PDynamicsHandler m_pDynamicsHandler;
};
