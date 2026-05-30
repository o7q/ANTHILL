#pragma once

#include "core/data_structures/chunk_map.hpp"
#include "core/time/time_handler.hpp"
#include "events/event_pool.hpp"
#include "events/particle/base.hpp"
#include "world/particle_handler/biome.hpp"
#include "world/particle_handler/dynamics/p_dynamics_handler.hpp"
#include "world/particle_handler/editor/particle_editor.hpp"
#include "world/particle_handler/navmesh/navmesh.hpp"
#include "world/particle_handler/particle.hpp"
#include "world/particle_handler/renderer/particle_renderer.hpp"

class ParticleHandler
{
  public:
    ParticleHandler(Vec2u chunkSize)
        : m_particles(chunkSize), m_biomeMarkers(chunkSize), m_background(chunkSize),
          m_dynamicsHandler(m_particles, m_navmesh), m_editor(m_particles, m_biomeMarkers, m_background),
          m_navmesh({8, 8})
    {
    }

    void update(TimeHandler::Info time, Rectangle_i updateRect);

    const ChunkMap<Particle> &getParticles() const { return m_particles; }
    const ChunkMap<BiomeID> &getBiomeMarkers() const { return m_biomeMarkers; }
    const ChunkMap<Color> &getBackground() const { return m_background; }
    const Navmesh &getNavmesh() const { return m_navmesh; }

    PDynamicsHandler &getDynamics() { return m_dynamicsHandler; }
    ParticleEditor &getEditor() { return m_editor; }
    ParticleRenderer &getRenderer() { return m_renderer; }

    EventPool<ParticleEvent> &getEvents() { return m_events; }

    template <typename QueryFunction>
    void query(Vec2i start, Vec2i end, QueryFunction &&query, bool skipNull = true) const
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
    ChunkMap<Color> m_background;

    PDynamicsHandler m_dynamicsHandler;
    ParticleEditor m_editor;
    ParticleRenderer m_renderer;
    Navmesh m_navmesh;

    EventPool<ParticleEvent> m_events;
};
