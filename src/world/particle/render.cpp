#include "particle_handler.hpp"

void ParticleHandler::render(Viewport &viewport, const Camera &camera)
{
    Vec2u viewport_size = viewport.getSize();

    for (unsigned int y = 0; y < viewport_size.y; ++y)
    {
        for (unsigned int x = 0; x < viewport_size.x; ++x)
        {
            Vec2i worldPos = camera.viewportToWorld(x, y, viewport);

            Particle *p = m_particles.get(worldPos.x, worldPos.y);

            if (!p)
            {
                continue;
            }

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

    for (auto &[index, data] : m_navmesh.getMesh())
    {
        if (data.containsSolid)
        {
            Vec2u res = m_navmesh.getResolution();
            Vec2i pos = camera.worldToViewport(index.x * res.x, index.y * res.y,
                                               viewport);

            viewport.setPixel(pos.x, pos.y, Color(100, 0, 255));
        }
    }
}
