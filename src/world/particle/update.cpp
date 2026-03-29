#include "events/event_emitter.hpp"
#include "events/particle/base.hpp"
#include "particle_handler.hpp"

void ParticleHandler::update(float dt, Vec2i origin, Vec2i size)
{
    for (auto &event : m_events.getEmittedEvents())
    {
        std::visit(overloaded{[&](const ParticleDrawEvent &e)
                              {
                                  draw(e.position.x, e.position.y, e.particle,
                                       e.radius);
                              }},
                   event);
    }
    m_events.purge();
    m_pDynamicsHandler.update(dt, origin, size);
}
