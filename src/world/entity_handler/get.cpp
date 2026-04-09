#include "entity_handler.hpp"

Player *EntityHandler::getCurrentPlayer()
{
    Entity *e = getEntity(m_currentPlayerID);
    return e ? static_cast<Player *>(e) : nullptr;
}

Entity *EntityHandler::getLatestEntity() { return getEntity(m_latestEntityID); }

Entity *EntityHandler::getEntity(uint64_t id)
{
    auto it = m_entities.find(id);

    if (it == m_entities.end())
    {
        return nullptr;
    }

    return it->second.get();
}
