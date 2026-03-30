#pragma once

#include "backend/viewport/viewport.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/camera/camera.hpp"
#include "world/particle/particle.hpp"

class ParticleRenderer
{
  public:
    ParticleRenderer(ChunkMap<Particle> &particles) : r_particles(particles) {}

    void render(Viewport &viewport, const Camera &camera)
    {
        Vec2u viewport_size = viewport.getSize();

        for (unsigned int y = 0; y < viewport_size.y; ++y)
        {
            for (unsigned int x = 0; x < viewport_size.x; ++x)
            {
                Vec2i worldPos = camera.viewportToWorld(Vec2i(x, y), viewport);

                Particle *p = r_particles.get(worldPos);

                if (!p || p->isAir())
                {
                    continue;
                }

                viewport.setPixel({x, y}, p->getColor());
            }
        }
    }

  private:
    ChunkMap<Particle> &r_particles;
};
