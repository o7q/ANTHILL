#include "particle_handler.hpp"

void ParticleHandler::update(float dt, Vec2i origin, Vec2i size)
{
    for (auto &event : m_events.getEmittedEvents())
    {
        switch (event->type)
        {
        case ParticleEventType::Draw:
        {
            auto e = static_cast<ParticleDrawEvent *>(event.get());
            draw(e->position.x, e->position.y, e->particle, e->radius);
        }
        break;
        }
    }
    m_events.purge();
    m_pDynamicsHandler.update(dt, origin, size);
}
