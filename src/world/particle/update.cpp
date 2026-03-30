#include "particle_world.hpp"

void ParticleWorld::update(float dt, Vec2i origin, Vec2i size)
{
    for (auto &event : m_events.getEmittedEvents())
    {
        switch (event->type)
        {
            case ParticleEventType::Draw:
            auto e = static_cast<ParticleDrawEvent *>(event.get());
            m_editor.draw(e->position, e->particle, e->radius);
            break;
        }
    }
    m_events.purge();
    
    m_dynamicsHandler.update(dt, origin, size);
}
