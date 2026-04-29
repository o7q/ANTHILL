#include "entity_handler.hpp"

uint64_t EntityHandler::addEntity(std::unique_ptr<Entity> entity)
{
    uint64_t id      = m_idHandler.getNext();
    m_latestEntityID = id;
    m_entities[id]   = std::move(entity);
    return id;
}

uint64_t EntityHandler::addPlayer(std::unique_ptr<Player> player)
{
    m_currentPlayerID = addEntity(std::move(player));
    return m_currentPlayerID;
}
