#include "particle_world.hpp"

void ParticleWorld::update(float dt, Vec2i origin, Vec2u size)
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
    m_events.clear();
    m_dynamicsHandler.update(dt, origin, size);
}
