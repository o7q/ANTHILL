#pragma once

#include "assets/assets.hpp"
#include "camera/camera.hpp"
#include "core/data_structures/chunk_map.hpp"
#include "core/math/color.hpp"
#include "core/viewport/render_command.hpp"
#include "world/particle_handler/biome.hpp"
#include "world/particle_handler/particle.hpp"

class ParticleRenderer
{
  public:
    struct RenderData
    {
        const ChunkMap<Particle> &particles;
        const ChunkMap<BiomeID> &biomeMarkers;
        const ChunkMap<Color> &background;
        const Camera &camera;
        const Assets &assets;
    };

  public:
    ParticleRenderer() = default;

    void render(const RenderData &data, std::vector<RenderCommand> &commandsOut);

  private:
    void reconstruct_texture(Vec2u size) { m_texture = Texture(size); }
    void render_biome(const ChunkMap<BiomeID> &biomeMarkers, const Assets &assets, Vec2i worldPos,
                      Vec2i cameraPos, Vec2u screenPos);

  private:
    Texture m_texture;
};
