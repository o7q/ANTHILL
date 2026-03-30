#pragma once

#include "backend/viewport/viewport.hpp"
#include "events/event_emitter.hpp"
#include "events/particle/base.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/particle/dynamics/p_dynamics_handler.hpp"
#include "world/particle/editor/particle_editor.hpp"
#include "world/particle/navmesh/navmesh.hpp"
#include "world/particle/particle.hpp"
#include "world/particle/renderer/particle_renderer.hpp"

class ParticleWorld
{
  public:
    ParticleWorld()
        : m_particles({32, 32}), m_navmesh({8, 8}),
          m_dynamicsHandler(m_particles, m_navmesh), m_editor(m_particles),
          m_renderer(m_particles)
    {
    }

    void update(float dt, Vec2i origin, Vec2i size);
    void render(Viewport &viewport, const Camera &camera);

    const ChunkMap<Particle> &getParticles() const { return m_particles; }
    ChunkMap<Particle> &getParticles() { return m_particles; }
    const Navmesh &getNavmesh() const { return m_navmesh; }
    Navmesh &getNavmesh() { return m_navmesh; }
    PDynamicsHandler &getDynamics() { return m_dynamicsHandler; }
    ParticleEditor &getEditor() { return m_editor; }
    EventEmitter<ParticleEvent> &getEvents() { return m_events; }

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
    EventEmitter<ParticleEvent> m_events;
};
