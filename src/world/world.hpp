#pragma once

#include "events/event_pool.hpp"
#include "events/external/base.hpp"
#include "px/time/time_handler.hpp"
#include "px/canvas/draw_types.hpp"
#include "world/entity_handler/entity_handler.hpp"
#include "world/particle_handler/particle_handler.hpp"
#include <vector>

class World
{
  public:
    World(px::Vec2u chunkSize) : m_particleHandler(chunkSize) {}
    World(const World &other)            = delete;
    World &operator=(const World &other) = delete;

    void update(const px::TimeHandler &time, px::Vec2i origin, EventPool<ExternalEvent> &externalEvents);
    void render(const Camera &camera, const Assets &assets, std::vector<px::DrawCommand> &commandsOut);

    ParticleHandler &getParticleHandler() { return m_particleHandler; }
    EntityHandler &getEntityHandler() { return m_entityHandler; }

  private:
    ParticleHandler m_particleHandler;
    EntityHandler m_entityHandler;
};
