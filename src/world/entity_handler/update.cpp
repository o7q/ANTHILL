#include "entity_handler.hpp"

#include "events/event_pool.hpp"
#include "world/particle_handler/particle_handler.hpp"
#include <cstdint>
#include <memory>
#include <unordered_map>

void EntityHandler::update(const ParticleHandler &particleHandler, TimeHandler::Info time, Vec2i origin,
                           EventPoolRefs eventPoolRefs)
{
    EventPool<EntityEvent> events;

    const Player *currentPlayer = getCurrentPlayer();

    for (auto &[id, entity] : m_entities)
    {
        EntityUpdateContext context{
            id, time, particleHandler, get_other_entities(id), m_currentPlayerID, currentPlayer};

        entity->update(context, events);

        Vec2i pos = entity->getBody().getPosition();

        if (entity->getHealth() <= 0.0f || pos.x < origin.x - m_globalKillRadius.x ||
            pos.x > origin.x + m_globalKillRadius.x || pos.y < origin.y - m_globalKillRadius.y ||
            pos.y > origin.y + m_globalKillRadius.y)
        {
            m_entitiesToRemove.push_back(id);
        }
    }

    handle_events(events, eventPoolRefs);

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

std::unordered_map<uint64_t, const Entity *> EntityHandler::get_other_entities(uint64_t base)
{
    std::unordered_map<uint64_t, const Entity *> entities;
    entities.reserve(m_entities.size() - 1);

    for (auto &[id, entity] : m_entities)
    {
        if (id == base)
        {
            continue;
        }

        entities[id] = entity.get();
    }

    return entities;
}