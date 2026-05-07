#include "entity_handler.hpp"

const std::unordered_map<uint64_t, const Entity *> EntityHandler::get_nearby_entities(uint64_t nearID)
{
    std::unordered_map<uint64_t, const Entity *> nearby;
    for (auto &[id, entity] : m_entities)
    {
        if (nearID == id)
        {
            continue;
        }

        nearby[id] = entity.get();
    }
    return nearby;
}
