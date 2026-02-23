#pragma once

#include "engine/sparse_chunk_map.hpp"
#include "particle.hpp"
#include "world/particle_dynamics/p_dynamics_handler.hpp"

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

    void draw(int x, int y, Particle p, int radius)
    {
        int half_radius = radius / 2;
        for (int y_ = -half_radius; y_ <= half_radius; ++y_)
        {
            for (int x_ = -half_radius; x_ <= half_radius; ++x_)
            {

                if (y_ * y_ + x_ * x_ <= radius * radius)
                {
                    set(x + x_, y + y_, p);
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

  private:
    SparseChunkMap<Particle> m_particles;
    PDynamicsHandler m_pDynamicsHandler;
};
