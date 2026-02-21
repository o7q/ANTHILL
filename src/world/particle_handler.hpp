#pragma once

#include "engine/sparse_chunk_map.hpp"
#include "particle.hpp"
#include "world/dynamics/dynamics.hpp"
#include <iostream>

class ParticleHandler
{
  public:
    ParticleHandler() : m_particles(32, 32), m_dynamics(m_particles) {}

    void update(float dt) { m_dynamics.update(dt); }
    void applyForce(float x, float y, float power)
    {
        for (auto &[chunkPos, chunk] : m_particles.getChunks())
        {
            Vec2<unsigned int> chunkSize = m_particles.getChunkSize();
            for (unsigned int y = 0; y < chunkSize.y; ++y)
            {
                for (unsigned int x = 0; x < chunkSize.x; ++x)
                {
                    const int px = chunkPos.first * chunkSize.x + x;
                    const int py = chunkPos.second * chunkSize.y + y;
                    Particle p = m_particles.get(px, py);

                    if (p.getMatterType() != Particle::MatterType::Solid)
                    {
                        continue;
                    }

                    Vec2<float> offset =
                        (Vec2<float>(x, y) -
                         Vec2<float>(p.getVerlet().getPosition().x,
                                     p.getVerlet().getPosition().y)) *
                        power;

                    p.getVerlet().setPosition(px, py);
                    p.getVerlet().setForce(offset.x, offset.y);
                    m_particles.set(px, py, p);
                }
            }
        }
    }

    SparseChunkMap<Particle> &getParticles() { return m_particles; }

  private:
    SparseChunkMap<Particle> m_particles;
    ParticleDynamics m_dynamics;
};
