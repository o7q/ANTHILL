#include "entity_handler.hpp"

#include "events/entity/events.hpp"
#include "events/event_pool.hpp"
#include <memory>

void EntityHandler::handleEvents(EventPool<EntityEvent> &events, EventPoolRefs eventPoolRefs)
{
    for (auto &event : events.getEvents())
    {
        switch (event->type)
        {
        case EntityEventType::EntityDamage:
        {
            auto e = static_cast<EntityDamageEvent *>(event.get());

            uint64_t target = e->target;
            if (target == 0)
            {
                break;
            }

            auto it = m_entities.find(target);
            if (it == m_entities.end())
            {
                break;
            }

            it->second->damage(e->damage);
        }
        break;
        case EntityEventType::EntitySpawn:
        {
            auto e = static_cast<EntitySpawnEvent *>(event.get());
            m_entitiesToAdd.push_back(std::move(e->entity));
        }
        break;
        case EntityEventType::Particle:
        {
            auto e = static_cast<EntityParticleEvent *>(event.get());
            eventPoolRefs.particle.emit(std::move(e->payload));
        }
        break;
        case EntityEventType::Backend:
        {
            auto e = static_cast<EntityBackendEvent *>(event.get());
            eventPoolRefs.backend.emit(std::move(e->payload));
        }
        break;
        }
    }
}
