#include "entity_handler.hpp"

#include "px/viewport/render_command.hpp"

void EntityHandler::render(const Camera &camera, std::vector<RenderCommand> &commandsOut)
{
    for (auto &entityPair : m_entities)
    {
        Entity *entity = entityPair.second.get();
        entity->render(camera, commandsOut);
    }
}
