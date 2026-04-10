#include "entity_handler.hpp"

const std::unordered_map<uint64_t, const Entity *>
EntityHandler::getNearbyEntities()
{
    std::unordered_map<uint64_t, const Entity *> nearby;
    for (auto &[id, entity] : m_entities)
    {
        nearby[id] = entity.get();
    }
    return nearby;
}
