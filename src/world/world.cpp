#include "world.hpp"

void World::update(float dt)
{
    Vec2i cameraPos = m_camera.getPosition();

    m_particleWorld.update(dt, cameraPos, {500, 300});
    m_entityHandler.update(m_particleWorld, dt);
    m_camera.update(dt);
}

void World::render(Viewport &viewport)
{
    m_particleWorld.render(viewport, m_camera);
    m_entityHandler.render(viewport, m_camera);
}
