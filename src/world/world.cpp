#include "world.hpp"

#include "events/external/base.hpp"
#include "px/window/render_command.hpp"

void World::update(px::TimeHandler::Info time, px::Vec2i origin, EventPool<ExternalEvent> &externalEvents)
{
    m_particleHandler.update(time, origin);
    m_entityHandler.update(m_particleHandler, time, origin, {externalEvents, m_particleHandler.getEvents()});
}

void World::render(const Camera &camera, const Assets &assets, std::vector<px::RenderCommand> &commandsOut)
{
    m_particleHandler.getRenderer().render({m_particleHandler.getParticles(),
                                            m_particleHandler.getBiomeMarkers(),
                                            m_particleHandler.getBackground(), camera, assets},
                                           commandsOut);
    m_entityHandler.render(camera, commandsOut);
}
