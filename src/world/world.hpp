#pragma once

#include "backend/time/time_handler.hpp"
#include "backend/viewport/render_command.hpp"
#include "events/event_pool.hpp"
#include "events/external/base.hpp"
#include "world/entity_handler/entity_handler.hpp"
#include "world/particle_handler/particle_handler.hpp"
#include <vector>

class World
{
  public:
    World() {}
    World(const World &other)            = delete;
    World &operator=(const World &other) = delete;

    void update(TimeHandler::Info time, Vec2i origin, EventPool<ExternalEvent> &externalEvents);
    void render(const Camera &viewport, const Assets &assets, std::vector<RenderCommand> &commandsOut);

    ParticleHandler &getParticleHandler() { return m_particleHandler; }
    EntityHandler &getEntityHandler() { return m_entityHandler; }

  private:
    ParticleHandler m_particleHandler;
    EntityHandler m_entityHandler;
};
