#include "core/math/geometry/rectangle.hpp"
#include "entity_handler.hpp"

#include "core/math/distance.hpp"
#include "events/event_pool.hpp"
#include "world/particle_handler/particle_handler.hpp"
#include <cstdint>
#include <memory>
#include <unordered_map>

void EntityHandler::update(const ParticleHandler &particleHandler, TimeHandler::Info time, Vec2i origin,
                           EventPoolRefs eventPoolRefs)
{
    const Player *currentPlayer = getCurrentPlayer();
    Rectangle_i killBox(origin, m_globalKillRadius);

    for (auto &[id, entity] : m_entities)
    {
        if (!entity)
        {
            continue;
        }

        EventPool<EntityEvent> events;

        float distanceToCurrentPlayer = 0.0f;
        Vec2f vectorTowardsCurrentPlayer;

        if (currentPlayer)
        {
            distanceToCurrentPlayer = Math::Distance::euclidian(currentPlayer->getBody().getPositionFloat(),
                                                                entity->getBody().getPositionFloat());
            vectorTowardsCurrentPlayer =
                (currentPlayer->getBody().getPositionFloat() - entity->getBody().getPositionFloat())
                    .normalize();
        }

        std::unordered_map<uint64_t, const Entity *> otherEntities;
        get_other_entities(otherEntities, id);

        EntityUpdateContext context{id,
                                    time,
                                    particleHandler,
                                    otherEntities,
                                    m_currentPlayerID,
                                    currentPlayer,
                                    distanceToCurrentPlayer,
                                    vectorTowardsCurrentPlayer};

        entity->update(context, events);

        Vec2i pos = entity->getBody().getPosition();

        if (entity->getHealth() <= 0 || !killBox.pointInside(pos) || !particleHandler.getParticles().get(pos))
        {
            entity->onKill(context, events);
            entity.reset();
        }

        handle_events(events, eventPoolRefs);
    }

    for (auto it = m_entities.begin(); it != m_entities.end();)
    {
        if (!it->second)
        {
            it = m_entities.erase(it);
        }
        else
        {
            it++;
        }
    }

    for (std::unique_ptr<Entity> &newEntity : m_entitiesToAdd)
    {
        m_entities[m_idHandler.getNext()] = std::move(newEntity);
    }

    m_entitiesToAdd.clear();
}

void EntityHandler::get_other_entities(std::unordered_map<uint64_t, const Entity *> &out, uint64_t base)
{
    out.reserve(m_entities.size() - 1);

    for (auto &[id, entity] : m_entities)
    {
        if (id == base || !entity)
        {
            continue;
        }

        out[id] = entity.get();
    }
}
