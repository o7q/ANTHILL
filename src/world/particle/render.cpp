#include "particle_world.hpp"

void ParticleWorld::render(Viewport &viewport, const Camera &camera,
                           const Assets &assets)
{
    m_renderer.render(viewport, camera, assets);
}
