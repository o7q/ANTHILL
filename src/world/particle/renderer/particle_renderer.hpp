#pragma once

#include "assets/assets.hpp"
#include "backend/viewport/viewport.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/camera/camera.hpp"
#include "world/particle/particle.hpp"

class ParticleRenderer
{
  private:
    struct BackgroundRenderSettings
    {
        Vec2u viewportDrawPos;
        Vec2i cameraPos;
        Vec2i worldPos;
    };

  public:
    ParticleRenderer(ChunkMap<Particle> &particles) : r_particles(particles) {}

    void render(Viewport &viewport, const Camera &camera, const Assets &assets);

  private:
    void render_background(Viewport &viewport, const Assets &assets,
                           BackgroundRenderSettings settings);

    Vec2u calculate_parallax(Vec2i worldPos, Vec2i cameraPos, Vec2u size, float amount)
    {
        Vec2u parallax =
            (worldPos.toFloat() - cameraPos.toFloat() * amount).toUnsignedInt() %
            size;
        return parallax;
    }

  private:
    ChunkMap<Particle> &r_particles;
};
