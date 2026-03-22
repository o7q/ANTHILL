#include "entity_handler.hpp"

void EntityHandler::render(Viewport &viewport, const Camera &camera)
{
    for (auto &entityPair : m_entities)
    {
        Entity *entity = entityPair.second.get();

        if (!entity)
        {
            continue;
        }
        
        entity->render(viewport, camera);
    }
}
