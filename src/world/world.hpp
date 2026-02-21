#pragma once

#include "engine/camera.hpp"
#include "engine/window/viewport.hpp"
#include "world/particle_handler.hpp"

class World
{
  public:
    void render(const Camera &camera, Viewport &viewport)
    {
        Vec2<float> camera_pos = camera.getPosition();
        Vec2<unsigned int> viewport_size = viewport.getSize();

        for (unsigned int y = 0; y < viewport_size.y; ++y)
        {
            for (unsigned int x = 0; x < viewport_size.x; ++x)
            {
                Color pixel = m_particleHandler.getParticles()
                                  .get(x + camera_pos.x, y + camera_pos.y)
                                  .getColor();
                viewport.setPixel(x, y, pixel);
            }
        }
    }

    ParticleHandler &getParticleHandler() { return m_particleHandler; }

  private:
    ParticleHandler m_particleHandler;
};
