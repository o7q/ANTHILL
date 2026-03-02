#pragma once

#include "world/particle.hpp"
#include "world/particle_dynamics/p_dynamics_handler.hpp"
#include "world/sparse_chunk_map.hpp"

class ParticleHandler
{
  public:
    ParticleHandler() : m_particles(32, 32), m_pDynamicsHandler(m_particles) {}

    void update(float dt) { m_pDynamicsHandler.update(dt); }

    void set(int x, int y, Particle p);
    void draw(int x, int y, Particle p, int radius = 5);

    template <typename F> void query(Vec2<int> start, Vec2<int> end, F &query)
    {
        for (int y = start.y; y <= end.y; ++y)
        {
            for (int x = start.x; x <= end.x; ++x)
            {
                Particle *p = m_particles.get(x, y);

                if (!p)
                {
                    continue;
                }

                if (query(p))
                {
                    return;
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
