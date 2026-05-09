#include "particle_renderer.hpp"

#include "camera/camera.hpp"
#include "core/viewport/render_command.hpp"

void ParticleRenderer::render(const ChunkMap<Particle> &particles, const ChunkMap<BiomeID> &biomeMarkers,
                              const Camera &camera, const Assets &assets,
                              std::vector<RenderCommand> &commandsOut)
{
    Vec2u size = camera.getViewSize();

    if (m_texture.getSize() != size)
    {
        reconstruct_texture(size);
    }

    for (unsigned int y = 0; y < size.y; ++y)
    {
        for (unsigned int x = 0; x < size.x; ++x)
        {
            m_texture.setPixel({x, y}, Color());

            Vec2i cameraPos = camera.getPosition();
            Vec2i worldPos  = camera.viewportToCamera(Vec2i(x, y));

            BackgroundRenderSettings settings;
            settings.cameraPos = cameraPos;
            settings.worldPos  = worldPos;
            settings.drawPos   = {x, y};
            render_background(biomeMarkers, assets, settings);

            if (const Particle *p = particles.get(worldPos))
            {
                Color c = p->getColor();

                if (c.a != 0)
                {
                    m_texture.setPixel({x, y}, c);
                }
            }
        }
    }

    TextureRenderCommandData data;
    data.texture = &m_texture;
    data.origin  = {0, 0};

    RenderCommand command;
    command.index = 0;
    command.data  = data;

    commandsOut.push_back(command);
}

void ParticleRenderer::render_background(const ChunkMap<BiomeID> &biomeMarkers, const Assets &assets,
                                         BackgroundRenderSettings settings)
{
    const BiomeID *a = biomeMarkers.get(settings.worldPos);

    if (!a)
    {
        return;
    }

    const Texture *tex = nullptr;
    float amount       = 0.0f;
    switch (*a)
    {
    case BiomeID::DesertLayer1:
        tex    = &assets.textures().get(TextureID::SandBackground);
        amount = 0.0f;
        break;
    case BiomeID::DesertLayer2:
        tex    = &assets.textures().get(TextureID::SandBackground);
        amount = 0.2f;
        break;
    default:
        break;
    }

    if (!tex)
    {
        return;
    }

    Vec2u size     = tex->getSize();
    Vec2u parallax = calculate_parallax(settings.worldPos, settings.cameraPos, size, amount);

    Color c = tex->getPixel(parallax);
    m_texture.setPixel(settings.drawPos, c);
}
