#include "world.hpp"

void World::update(float dt)
{
    Vec2i cameraPos = m_camera.getPosition();
    m_particleHandler.getDynamics().setUpdateInfo(cameraPos.x, cameraPos.y, 8);

    m_particleHandler.update(dt);
    m_entityHandler.update(m_particleHandler, dt);
    m_camera.update(dt);
}

void World::render(Viewport &viewport)
{
    m_particleHandler.render(viewport, m_camera);
    m_entityHandler.render(viewport, m_camera);
}
