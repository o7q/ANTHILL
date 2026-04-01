#include "world.hpp"

void World::update(float dt)
{
    Vec2i cameraPos = m_camera.getPosition();

    m_particleWorld.update(dt, cameraPos, {0, 0});
    m_entityHandler.update(m_particleWorld, dt);
}

void World::render(Viewport &viewport, const Assets &assets)
{
    m_particleWorld.render(viewport, m_camera, assets);
    m_entityHandler.render(viewport, m_camera);
}
