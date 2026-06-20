#include "entity_handler.hpp"

#include "px/window/render_command.hpp"

void EntityHandler::render(const Camera &camera, std::vector<px::RenderCommand> &commandsOut)
{
    for (auto &entityPair : m_entities)
    {
        Entity *entity = entityPair.second.get();
        entity->render(camera, commandsOut);
    }
}
