#include "entity_handler.hpp"

#include "px/canvas/draw_types.hpp"

void EntityHandler::render(const Camera &camera, std::vector<px::DrawCommand> &commandsOut)
{
    for (auto &entityPair : m_entities)
    {
        Entity *entity = entityPair.second.get();
        entity->render(camera, commandsOut);
    }
}
