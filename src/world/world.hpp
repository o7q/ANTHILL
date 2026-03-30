#pragma once

#include "backend/viewport/viewport.hpp"
#include "events/backend/base.hpp"
#include "events/event_emitter.hpp"
#include "world/camera/camera.hpp"
#include "world/entity_handler/entity_handler.hpp"
#include "world/generator/generator.hpp"
#include "world/particle/particle_handler.hpp"

class World
{
  public:
    World(EventEmitter<BackendEvent> &backendEvents)
        : r_backendEvents(backendEvents), m_generator(m_particleHandler),
          m_entityHandler(r_backendEvents, m_particleHandler.getEvents())
    {
    }
    World(const World &other) = delete;
    World &operator=(const World &other) = delete;

    void update(float dt);
    void render(Viewport &viewport);

    ParticleHandler &getParticleHandler() { return m_particleHandler; }
    EntityHandler &getEntityHandler() { return m_entityHandler; }

    Camera &getCamera() { return m_camera; }

    Generator &getGenerator() { return m_generator; }

  private:
    EventEmitter<BackendEvent> &r_backendEvents;

    ParticleHandler m_particleHandler;
    Generator m_generator;
    EntityHandler m_entityHandler;
    Camera m_camera;
};
