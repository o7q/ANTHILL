#pragma once

#include "engine/backend/viewport.hpp"
#include "engine/camera.hpp"
#include "engine/world/particle_handler.hpp"

class World
{
  public:
    void render(Viewport &viewport, const Camera &camera)
    {
        Vec2<unsigned int> viewport_size = viewport.getSize();
        Vec2<float> camera_pos = camera.getPosition();

        for (unsigned int y = 0; y < viewport_size.y; ++y)
        {
            for (unsigned int x = 0; x < viewport_size.x; ++x)
            {

                Vec2<int> pp =
                    Vec2<int>(x + camera_pos.x - viewport_size.x / 2.0f,
                              y + camera_pos.y - viewport_size.y / 2.0f);

                if (Particle *p =
                        m_particleHandler.getParticles().get(pp.x, pp.y))
                {
                    Color pixel = p->getColor();

                    if (p->isAir())
                    {
                        pixel = Color(50, 0, 0);
                    }

                    viewport.setPixel(x, y, pixel);
                }
            }
        }
    }

    ParticleHandler &getParticleHandler() { return m_particleHandler; }

  private:
    ParticleHandler m_particleHandler;
};
