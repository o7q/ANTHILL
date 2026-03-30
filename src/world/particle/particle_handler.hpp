#pragma once

#include "backend/texture/texture.hpp"
#include "backend/viewport/viewport.hpp"
#include "events/event_emitter.hpp"
#include "events/particle/base.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/camera/camera.hpp"
#include "world/particle/dynamics/p_dynamics_handler.hpp"
#include "world/particle/navmesh.hpp"
#include "world/particle/particle.hpp"

class ParticleHandler
{
  public:
    ParticleHandler()
        : m_particles(32, 32), m_navmesh({8, 8}),
          m_pDynamicsHandler(m_particles, m_navmesh)
    {
    }

    void update(float dt, Vec2i origin, Vec2i size);

    void set(int x, int y, Particle p);
    void draw(int x, int y, Particle p, int radius = 5);

    void textureToParticles(const Texture &texture, Vec2i pos,
                            Particle particleBase);

    template <typename QueryFunction>
    void query(Vec2i start, Vec2i end, QueryFunction &&query,
               bool skipNull = true) const
    {
        for (int y = start.y; y <= end.y; ++y)
        {
            for (int x = start.x; x <= end.x; ++x)
            {
                const Particle *p = m_particles.get(x, y);

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

    void render(Viewport &viewport, const Camera &camera);

    const Navmesh &getNavmesh() const { return m_navmesh; }

    const ChunkMap<Particle> &getRawParticles() const { return m_particles; }
    PDynamicsHandler &getDynamics() { return m_pDynamicsHandler; }

    EventEmitter<ParticleEvent> &getEvents() { return m_events; }

  private:
    ChunkMap<Particle> m_particles;
    Navmesh m_navmesh;
    PDynamicsHandler m_pDynamicsHandler;

    EventEmitter<ParticleEvent> m_events;
};
