#include "entity_handler.hpp"

void EntityHandler::addEntity(std::unique_ptr<Entity> entity)
{
    m_latestEntity = entity.get();
    m_entities[entity->getID()] = std::move(entity);
}

void EntityHandler::addPlayer(std::unique_ptr<Player> player)
{
    m_currentPlayer = player.get();
    addEntity(std::move(player));
}
