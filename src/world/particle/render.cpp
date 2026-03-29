#include "math/perlin.hpp"
#include "particle_handler.hpp"
#include "world/particle/navmesh.hpp"
#include <iostream>

void ParticleHandler::render(Viewport &viewport, const Camera &camera)
{
    Vec2u viewport_size = viewport.getSize();

    for (unsigned int y = 0; y < viewport_size.y; ++y)
    {
        for (unsigned int x = 0; x < viewport_size.x; ++x)
        {
            Vec2i worldPos = camera.viewportToWorld(x, y, viewport);

            Particle *p = m_particles.get(worldPos.x, worldPos.y);

            // float test = Math::Perlin::sampleEx(x, y, 10, 1, 14);
            // viewport.setPixel(x, y, Color(255*test, 255*test, 255*test));


            if (!p)
            {
                continue;
            }

            Color pixel = p->getColor();
            if (!p->isAir())
            {
                viewport.setPixel(x, y, pixel);
            }
        }
    }
}
