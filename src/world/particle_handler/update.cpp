#include "particle_handler.hpp"

#include "events/particle/events.hpp"

void ParticleHandler::update(TimeHandler::Info time, Vec2i origin)
{
    for (auto &event : m_events.getEvents())
    {
        switch (event->type)
        {
        case ParticleEventType::SetRadius:
        {
            auto e = static_cast<ParticleSetRadiusEvent *>(event.get());
            m_editor.setRadius(e->position, e->particle, e->radius);
            break;
        }
        case ParticleEventType::ApplyForce:
        {
            auto e = static_cast<ParticleApplyForceEvent *>(event.get());
            m_dynamicsHandler.applyForce(e->position, e->radius, e->power);
            break;
        }
        }
    }
    m_events.flush();
    m_dynamicsHandler.update(time, origin);
}
