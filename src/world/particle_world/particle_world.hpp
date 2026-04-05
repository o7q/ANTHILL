#pragma once

#include "events/event_pool.hpp"
#include "events/particle/base.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/particle_world/dynamics/p_dynamics_handler.hpp"
#include "world/particle_world/editor/particle_editor.hpp"
#include "world/particle_world/navmesh/navmesh.hpp"
#include "world/particle_world/particle.hpp"
#include "world/particle_world/renderer/particle_renderer.hpp"

class ParticleWorld
{
  public:
    ParticleWorld()
        : m_particles({32, 32}), m_navmesh({8, 8}),
          m_dynamicsHandler(m_particles, m_navmesh), m_editor(m_particles),
          m_renderer(m_particles)
    {
    }

    void update(float dt, Vec2i origin, Vec2u size);

    const ChunkMap<Particle> &getParticles() const { return m_particles; }
    ChunkMap<Particle> &getParticles() { return m_particles; }
    const Navmesh &getNavmesh() const { return m_navmesh; }
    Navmesh &getNavmesh() { return m_navmesh; }
    PDynamicsHandler &getDynamics() { return m_dynamicsHandler; }
    ParticleEditor &getEditor() { return m_editor; }
    ParticleRenderer &getRenderer() { return m_renderer; }
    EventPool<ParticleEvent> &getEvents() { return m_events; }

    template <typename QueryFunction>
    void query(Vec2i start, Vec2i end, QueryFunction &&query,
               bool skipNull = true) const
    {
        for (int y = start.y; y <= end.y; ++y)
        {
            for (int x = start.x; x <= end.x; ++x)
            {
                const Particle *p = m_particles.get({x, y});

                if (!p && skipNull)
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

  private:
    ChunkMap<Particle> m_particles;
    Navmesh m_navmesh;
    PDynamicsHandler m_dynamicsHandler;
    ParticleEditor m_editor;
    ParticleRenderer m_renderer;
    EventPool<ParticleEvent> m_events;
};
