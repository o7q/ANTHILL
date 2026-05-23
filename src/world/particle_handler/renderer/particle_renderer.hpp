#pragma once

#include "assets/assets.hpp"
#include "camera/camera.hpp"
#include "core/data_structures/chunk_map.hpp"
#include "core/viewport/render_command.hpp"
#include "world/particle_handler/biome.hpp"
#include "world/particle_handler/particle.hpp"

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
    ParticleRenderer() = default;

    void render(const ChunkMap<Particle> &particles, const ChunkMap<BiomeID> &biomeMarkers,
                const Camera &camera, const Assets &assets, std::vector<RenderCommand> &commandsOut);

  private:
    void reconstruct_texture(Vec2u size) { m_texture = Texture(size); }
    void render_background(const ChunkMap<BiomeID> &biomeMarkers, const Assets &assets,
                           BackgroundRenderSettings settings);

    Vec2u calculate_parallax(Vec2i worldPos, Vec2i cameraPos, Vec2u textureSize, float amount)
    {
        Vec2u parallax = (worldPos.toFloat() - cameraPos.toFloat() * amount).toUnsignedInt() % textureSize;
        return parallax;
    }

  private:
    Texture m_texture;
};
