#pragma once

#include "backend/texture/texture.hpp"
#include "backend/viewport/viewport.hpp"
#include "event/event_emitter.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/camera/camera.hpp"
#include "world/particle/dynamics/p_dynamics_handler.hpp"
#include "world/particle/events/event.hpp"
#include "world/particle/particle.hpp"

class ParticleHandler
{
  public:
    ParticleHandler() : m_particles(32, 32), m_pDynamicsHandler(m_particles) {}

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

    ChunkMap<Particle> &getParticles() { return m_particles; }
    const ChunkMap<Particle> &getParticles() const { return m_particles; }
    PDynamicsHandler &getDynamics() { return m_pDynamicsHandler; }

    EventEmitter<ParticleEvent> &getEvents() { return m_events; }

  private:
    ChunkMap<Particle> m_particles;
    PDynamicsHandler m_pDynamicsHandler;

    EventEmitter<ParticleEvent> m_events;
};
