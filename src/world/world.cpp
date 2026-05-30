#include "world.hpp"

#include "core/viewport/render_command.hpp"
#include "events/external/base.hpp"

void World::update(TimeHandler::Info time, Rectangle_i updateRect, EventPool<ExternalEvent> &externalEvents)
{
    m_particleHandler.update(time, updateRect);
    m_entityHandler.update(m_particleHandler, time, updateRect,
                           {externalEvents, m_particleHandler.getEvents()});
}

void World::render(const Camera &camera, const Assets &assets, std::vector<RenderCommand> &commandsOut)
{
    m_particleHandler.getRenderer().render({m_particleHandler.getParticles(),
                                            m_particleHandler.getBiomeMarkers(),
                                            m_particleHandler.getBackground(), camera, assets},
                                           commandsOut);
    m_entityHandler.render(camera, commandsOut);
}
