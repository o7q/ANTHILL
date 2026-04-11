#pragma once

#include "backend/viewport/render_command.hpp"
#include "events/backend/base.hpp"
#include "events/event_pool.hpp"
#include "world/entity_handler/entity_handler.hpp"
#include "world/generator/generator.hpp"
#include "world/particle_world/particle_world.hpp"
#include <vector>

class World
{
  public:
    World() : m_generator(m_particleWorld) {}
    World(const World &other) = delete;
    World &operator=(const World &other) = delete;

    void update(float dt, Vec2i origin, EventPool<BackendEvent> &backendEvents);

    void render(const Camera &viewport, const Assets &assets,
                std::vector<RenderCommand> &commandsOut);

    ParticleWorld &getParticleWorld() { return m_particleWorld; }
    Generator &getGenerator() { return m_generator; }
    EntityHandler &getEntityHandler() { return m_entityHandler; }

  private:
    ParticleWorld m_particleWorld;
    Generator m_generator;
    EntityHandler m_entityHandler;
};
