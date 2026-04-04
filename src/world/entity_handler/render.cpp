#include "backend/viewport/render_command.hpp"
#include "entity_handler.hpp"

std::vector<RenderCommand> EntityHandler::render(const Camera &camera)
{
    std::vector<RenderCommand> commands;

    for (auto &entityPair : m_entities)
    {
        Entity *entity = entityPair.second.get();

        if (!entity)
        {
            continue;
        }

        std::vector<RenderCommand> entityCommands = entity->render(camera);

        commands.insert(commands.end(), entityCommands.begin(),
                        entityCommands.end());
    }

    return commands;
}
