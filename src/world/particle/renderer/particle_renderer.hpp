#pragma once

#include "assets/assets.hpp"
#include "backend/viewport/render_command.hpp"
#include "camera/camera.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/particle/particle.hpp"

class ParticleRenderer
{
  private:
    struct BackgroundRenderSettings
    {
        Vec2u drawPos;
        Vec2i cameraPos;
        Vec2i worldPos;
    };

  public:
    ParticleRenderer(ChunkMap<Particle> &particles) : r_particles(particles) {}

    std::vector<RenderCommand> render(const Camera &camera,
                                      const Assets &assets);

    void reconstructTexture(Vec2u size) { m_texture = Texture(size); }

  private:
    void render_background(const Assets &assets,
                           BackgroundRenderSettings settings);

    Vec2u calculate_parallax(Vec2i worldPos, Vec2i cameraPos, Vec2u size,
                             float amount)
    {
        Vec2u parallax = (worldPos.toFloat() - cameraPos.toFloat() * amount)
                             .toUnsignedInt() %
                         size;
        return parallax;
    }

  private:
    ChunkMap<Particle> &r_particles;
    Texture m_texture;
};
