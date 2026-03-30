#include "particle_world.hpp"

void ParticleWorld::render(Viewport &viewport, const Camera &camera)
{
    m_renderer.render(viewport, camera);
}
