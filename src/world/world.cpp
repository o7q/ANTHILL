#include "world.hpp"

void World::update(float dt)
{
    Vec2i cameraPos = m_camera.getPosition();

    m_particleHandler.update(dt, cameraPos, {500, 300});
    m_entityHandler.update(m_particleHandler, dt);
    m_camera.update(dt);
}

void World::render(Viewport &viewport)
{
    m_particleHandler.render(viewport, m_camera);
    m_entityHandler.render(viewport, m_camera);
}
