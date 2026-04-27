#include "entity_handler.hpp"
#include "events/event_pool.hpp"
#include "world/particle_handler/particle_handler.hpp"
#include <memory>
#include <unordered_map>

void EntityHandler::update(const ParticleHandler &particleHandler, float dt,
                           Vec2i origin, EventPoolRefs eventPoolRefs)
{
    EventPool<EntityEvent> events;

    for (auto &[id, entity] : m_entities)
    {
        std::unordered_map<uint64_t, const Entity *> nearby =
            getNearbyEntities(id);
        EntityUpdateContext context{id, dt, particleHandler, nearby};

        entity->update(context, events);

        Vec2i pos = entity->getBody().getPosition();

        if (entity->getHealth() <= 0.0f ||
            pos.x < origin.x - m_globalKillRadius.x ||
            pos.x > origin.x + m_globalKillRadius.x ||
            pos.y < origin.y - m_globalKillRadius.y ||
            pos.y > origin.y + m_globalKillRadius.y)
        {
            m_entitiesToRemove.push_back(id);
        }
    }

    handleEvents(events, eventPoolRefs);

    for (uint64_t id : m_entitiesToRemove)
    {
        m_entities.erase(id);
    }

    for (std::unique_ptr<Entity> &newEntity : m_entitiesToAdd)
    {
        m_entities[m_idHandler.getNext()] = std::move(newEntity);
    }

    m_entitiesToRemove.clear();
    m_entitiesToAdd.clear();
}
