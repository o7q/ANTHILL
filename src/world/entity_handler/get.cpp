#include "entity_handler.hpp"

Player *EntityHandler::getCurrentPlayer()
{
    Entity *playerEntity = getEntity(m_currentPlayerID);
    return playerEntity ? static_cast<Player *>(playerEntity) : nullptr;
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
