#include "world.hpp"

#include "backend/viewport/render_command.hpp"
#include "events/scene/base.hpp"

void World::update(TimeHandler::Info time, Vec2i origin, EventPool<SceneEvent> &sceneEvents)
{
    m_particleHandler.update(time, origin);
    m_entityHandler.update(m_particleHandler, time, origin, {sceneEvents, m_particleHandler.getEvents()});
}

void World::render(const Camera &camera, const Assets &assets, std::vector<RenderCommand> &commandsOut)
{
    m_particleHandler.getRenderer().render(m_particleHandler.getParticles(),
                                           m_particleHandler.getBiomeMarkers(), camera, assets, commandsOut);
    m_entityHandler.render(camera, commandsOut);
}
