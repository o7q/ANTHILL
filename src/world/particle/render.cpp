#include "particle_handler.hpp"

void ParticleHandler::render(Viewport &viewport, const Camera &camera)
{
    Vec2u viewport_size = viewport.getSize();

    for (unsigned int y = 0; y < viewport_size.y; ++y)
    {
        for (unsigned int x = 0; x < viewport_size.x; ++x)
        {
            Vec2i pp = camera.viewportToWorld(x, y, viewport);

            if (Particle *p = m_particles.get(pp.x, pp.y))
            {
                Color pixel = p->getColor();
                if (!p->isAir())
                {
                    viewport.setPixel(x, y, pixel);
                }
                else
                {
                    viewport.setPixel(x, y, Color(100, 0, 0));
                }
            }
        }
    }
}
