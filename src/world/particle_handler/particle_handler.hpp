#pragma once

#include "events/event_pool.hpp"
#include "events/particle/base.hpp"
#include "px/data_structures/chunk_map.hpp"
#include "px/time/time_handler.hpp"
#include "world/particle_handler/biome.hpp"
#include "world/particle_handler/dynamics/p_dynamics_handler.hpp"
#include "world/particle_handler/editor/particle_editor.hpp"
#include "world/particle_handler/navmesh/navmesh.hpp"
#include "world/particle_handler/particle.hpp"
#include "world/particle_handler/renderer/particle_renderer.hpp"

class ParticleHandler
{
  public:
    ParticleHandler(px::Vec2u chunkSize)
        : m_particles(chunkSize), m_biomeMarkers(chunkSize), m_background(chunkSize),
          m_dynamicsHandler(m_particles, m_navmesh), m_editor(m_particles, m_biomeMarkers, m_background),
          m_navmesh({8, 8})
    {
    }

    void update(px::TimeHandler::Info time, px::Vec2i origin);

    const px::ChunkMap<Particle> &getParticles() const { return m_particles; }
    const px::ChunkMap<BiomeID> &getBiomeMarkers() const { return m_biomeMarkers; }
    const px::ChunkMap<px::Color> &getBackground() const { return m_background; }
    const Navmesh &getNavmesh() const { return m_navmesh; }

    PDynamicsHandler &getDynamics() { return m_dynamicsHandler; }
    ParticleEditor &getEditor() { return m_editor; }
    ParticleRenderer &getRenderer() { return m_renderer; }

    EventPool<ParticleEvent> &getEvents() { return m_events; }

    template <typename QueryFunction>
    void query(px::Vec2i start, px::Vec2i end, QueryFunction &&query, bool skipNull = true) const
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
    px::ChunkMap<Particle> m_particles;
    px::ChunkMap<BiomeID> m_biomeMarkers;
    px::ChunkMap<px::Color> m_background;

    PDynamicsHandler m_dynamicsHandler;
    ParticleEditor m_editor;
    ParticleRenderer m_renderer;
    Navmesh m_navmesh;

    EventPool<ParticleEvent> m_events;
};
