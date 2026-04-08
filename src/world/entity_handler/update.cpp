#include "entity_handler.hpp"
#include "events/entity/base.hpp"
#include "events/event_pool.hpp"
#include "world/particle_world/particle_world.hpp"
#include <memory>

void EntityHandler::update(const ParticleWorld &world, float dt,
                           EventPoolRefs eventPoolRefs)
{
    EventPool<EntityEvent> events;

    for (auto &entityPair : m_entities)
    {
        Entity *entity = entityPair.second.get();

        std::vector<const Entity *> nearby = getNearbyEntities(/*entity*/);
        EntityUpdateContext context{dt, world, nearby, m_currentPlayer};
        entity->update(context, events);

        if (entity->getHealth() <= 0.0f)
        {
            m_entitiesToRemove.push_back(entity->getID());
        }
    }

    handleEvents(events, eventPoolRefs);

    for (uint64_t id : m_entitiesToRemove)
    {
        m_entities.erase(id);
    }

    for (std::unique_ptr<Entity> &newEntity : m_entitiesToAdd)
    {
        m_entities[newEntity->getID()] = std::move(newEntity);
    }

    m_entitiesToAdd.clear();
    m_entitiesToRemove.clear();
}
