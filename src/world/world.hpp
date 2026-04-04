#pragma once

#include "events/backend/base.hpp"
#include "events/event_pool.hpp"
#include "world/entity_handler/entity_handler.hpp"
#include "world/generator/generator.hpp"
#include "world/particle/particle_world.hpp"
#include <vector>

class World
{
  public:
    World(EventPool<BackendEvent> &backendEvents)
        : r_backendEvents(backendEvents), m_generator(m_particleWorld),
          m_entityHandler(r_backendEvents, m_particleWorld.getEvents())
    {
    }
    World(const World &other) = delete;
    World &operator=(const World &other) = delete;

    void update(float dt, Vec2i origin);

    std::vector<RenderCommand> render(const Camera &viewport,
                                      const Assets &assets);

    ParticleWorld &getParticleWorld() { return m_particleWorld; }
    Generator &getGenerator() { return m_generator; }
    EntityHandler &getEntityHandler() { return m_entityHandler; }

  private:
    EventPool<BackendEvent> &r_backendEvents;

    ParticleWorld m_particleWorld;
    Generator m_generator;
    EntityHandler m_entityHandler;
};
