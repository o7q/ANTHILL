#include "entity_handler.hpp"

const std::vector<const Entity *>
EntityHandler::getNearbyEntities(const Entity *entity)
{
    std::vector<const Entity *> nearby;
    for (auto &entity : m_entities)
    {
        nearby.push_back(entity.second.get());
    }
    return nearby;
}
