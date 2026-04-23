#pragma once

#include "events/event_pool.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/particle_handler/biome.hpp"
#include "world/particle_handler/dynamics/p_dynamics_handler.hpp"
#include "world/particle_handler/editor/particle_editor.hpp"
#include "world/particle_handler/events/base.hpp"
#include "world/particle_handler/navmesh/navmesh.hpp"
#include "world/particle_handler/particle.hpp"
#include "world/particle_handler/renderer/particle_renderer.hpp"

class ParticleHandler
{
  public:
    ParticleHandler()
        : m_particles({32, 32}), m_biomeMarkers({32, 32}), m_navmesh({8, 8}),
          m_dynamicsHandler(m_particles, m_navmesh), m_editor(m_particles)
    {
    }

    void update(float dt, Vec2i origin);

    const ChunkMap<Particle> &getParticles() const { return m_particles; }
    ChunkMap<Particle> &getParticles() { return m_particles; }

    const ChunkMap<BiomeID> &getBiomeMarkers() const { return m_biomeMarkers; }
    ChunkMap<BiomeID> &getBiomeMarkers() { return m_biomeMarkers; }

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
    ChunkMap<BiomeID> m_biomeMarkers;

    Navmesh m_navmesh;

    PDynamicsHandler m_dynamicsHandler;
    ParticleEditor m_editor;
    ParticleRenderer m_renderer;

    EventPool<ParticleEvent> m_events;
};
