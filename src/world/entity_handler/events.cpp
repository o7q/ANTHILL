#include "entity_handler.hpp"

#include "events/entity/events.hpp"
#include "events/event_pool.hpp"
#include <memory>

void EntityHandler::handle_events(EventPool<EntityEvent> &events, EventPoolRefs eventPoolRefs)
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

            Entity *entity = it->second.get();

            entity->damage(e->source);

            if (entity->getHealth() <= 0)
            {
                it->second.reset();
            }
        }
        break;
        case EntityEventType::EntityKill:
        {
            auto e = static_cast<EntityKillEvent *>(event.get());

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

            it->second.reset();
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
        case EntityEventType::External:
        {
            auto e = static_cast<EntityExternalEvent *>(event.get());
            eventPoolRefs.external.emit(std::move(e->payload));
        }
        break;
        }
    }
}
