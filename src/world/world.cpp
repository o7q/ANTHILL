#include "world.hpp"

void World::update(float dt)
{
    m_particleHandler.update(dt);
    m_entityHandler.update(dt);
}

void World::render(Viewport &viewport, const Camera &camera)
{
    m_particleHandler.render(viewport, camera);
    m_entityHandler.render(viewport, camera);
}
