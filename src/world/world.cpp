#include "world.hpp"
#include "backend/viewport/render_command.hpp"

void World::update(float dt, Vec2i origin)
{
    m_particleWorld.update(dt, origin, {0, 0});
    m_entityHandler.update(m_particleWorld, dt);
}

std::vector<RenderCommand> World::render(const Camera &camera,
                                         const Assets &assets)
{
    std::vector<RenderCommand> particleRenderCommands =
        m_particleWorld.getRenderer().render(camera, assets);
    std::vector<RenderCommand> entityRenderCommands =
        m_entityHandler.render(camera);

    std::vector<RenderCommand> out;
    out.insert(out.end(), particleRenderCommands.begin(),
               particleRenderCommands.end());
    out.insert(out.end(), entityRenderCommands.begin(),
               entityRenderCommands.end());
    return out;
}
