#include "world.hpp"
#include "backend/viewport/render_command.hpp"

void World::update(float dt, Vec2i origin, EventPool<BackendEvent> &backendEvents)
{
    m_particleHandler.update(dt, origin);
    m_entityHandler.update(m_particleHandler, dt, origin,
                           {backendEvents, m_particleHandler.getEvents()});
}

void World::render(const Camera &camera, const Assets &assets,
                   std::vector<RenderCommand> &commandsOut)
{
    m_particleHandler.getRenderer().render(m_particleHandler.getParticles(),
                                           m_particleHandler.getBiomeMarkers(), camera, assets,
                                           commandsOut);
    m_entityHandler.render(camera, commandsOut);
}
