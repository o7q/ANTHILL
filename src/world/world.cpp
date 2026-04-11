#include "world.hpp"
#include "backend/viewport/render_command.hpp"

void World::update(float dt, Vec2i origin,
                   EventPool<BackendEvent> &backendEvents)
{
    m_particleWorld.update(dt, origin);
    m_entityHandler.update(m_particleWorld, dt, origin,
                           {backendEvents, m_particleWorld.getEvents()});
}

void World::render(const Camera &camera, const Assets &assets,
                   std::vector<RenderCommand> &commandsOut)
{
    m_particleWorld.getRenderer().render(camera, assets, commandsOut);
    m_entityHandler.render(camera, commandsOut);
}
