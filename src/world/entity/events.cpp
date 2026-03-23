#include "entity_handler.hpp"

void EntityHandler::handleEvents(Entity *entity)
{
    EntityEventEmitter &currentEmitter = entity->getEventEmitter();

    for (auto &e : currentEmitter.getEmittedEvents())
    {
        switch (e->type)
        {
        case EntityEventType::EntityDamage:
        {
            EntityDamageEvent *event =
                static_cast<EntityDamageEvent *>(e.get());

            uint64_t target = event->target;
            if (target)
            {
                m_entities[target]->damage(event->damage);
            }
        }
        break;
        case EntityEventType::EntitySpawn:
        {
            EntitySpawnEvent *event = static_cast<EntitySpawnEvent *>(e.get());

            m_entitiesToAdd.push_back(
                event->entityFactory(m_idHandler.getNext()));
        }
        break;
        case EntityEventType::WorldModifyDraw:
        {
            EntityWorldModifyDrawEvent *event =
                static_cast<EntityWorldModifyDrawEvent *>(e.get());

            r_particleHandler.draw(event->pos.x, event->pos.y, event->particle,
                                   event->radius);
        }
        break;
        }
    }

    currentEmitter.purge();
}
