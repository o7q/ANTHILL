#pragma once

#include "assets/assets.hpp"
#include "camera/camera.hpp"
#include "px/basic_types/color.hpp"
#include "px/data_structures/chunk_map.hpp"
#include "px/window/render_command.hpp"
#include "world/particle_handler/biome.hpp"
#include "world/particle_handler/particle.hpp"

class ParticleRenderer
{
  public:
    struct RenderData
    {
        const px::ChunkMap<Particle> &particles;
        const px::ChunkMap<BiomeID> &biomeMarkers;
        const px::ChunkMap<px::Color> &background;
        const Camera &camera;
        const Assets &assets;
    };

  public:
    ParticleRenderer() = default;

    void render(const RenderData &data, std::vector<px::RenderCommand> &commandsOut);

  private:
    void reconstruct_texture(px::Vec2u size) { m_texture = px::Texture(size); }
    void render_biome(const px::ChunkMap<BiomeID> &biomeMarkers, const Assets &assets, px::Vec2i worldPos,
                      px::Vec2i cameraPos, px::Vec2u screenPos);

  private:
    px::Texture m_texture;
};
