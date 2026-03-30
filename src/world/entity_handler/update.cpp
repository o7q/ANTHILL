#include "entity_handler.hpp"
#include <memory>

void EntityHandler::update(const ParticleHandler &particleHandler, float dt)
{
    for (auto &entityPair : m_entities)
    {
        Entity *entity = entityPair.second.get();

        std::vector<const Entity *> nearby = getNearbyEntities(entity);
        EntityUpdateContext context{dt, particleHandler, nearby};
        entity->update(context);

        handleEvents(entity->getEventEmitter());

        if (entity->isDead())
        {
            m_entitiesToRemove.push_back(entity->getID());
        }
    }

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
