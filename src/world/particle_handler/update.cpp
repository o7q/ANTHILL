#include "particle_handler.hpp"

#include "events/particle/events.hpp"

void ParticleHandler::update(TimeHandler::Info time, Vec2i origin)
{
    for (auto &event : m_events.getEvents())
    {
        switch (event->type)
        {
        case ParticleEventType::Draw:
            auto e = static_cast<ParticleDrawEvent *>(event.get());
            m_editor.draw(e->position, e->particle, e->radius);
            break;
        }
    }
    m_events.flush();
    m_dynamicsHandler.update(time, origin);
}
