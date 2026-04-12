#include "particle_renderer.hpp"
#include "backend/viewport/render_command.hpp"
#include "camera/camera.hpp"

void ParticleRenderer::render(const ChunkMap<Particle> &particles,
                              const ChunkMap<BiomeID> &biomeMarkers,
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
            Vec2i worldPos = camera.viewportToCamera(Vec2i(x, y));

            const Particle *p = particles.get(worldPos);

            if (!p)
            {
                continue;
            }

            if (p->isAir())
            {
                BackgroundRenderSettings settings;
                settings.cameraPos = cameraPos;
                settings.worldPos = worldPos;
                settings.drawPos = {x, y};
                render_background(biomeMarkers, assets, settings);
            }
            else
            {
                Color c = p->getColor();
                m_texture.setPixel({x, y}, c);
            }
        }
    }

    TextureRenderCommandData data;
    data.texture = &m_texture;
    data.origin = {0, 0};

    RenderCommand command;
    command.index = 0;
    command.data = data;

    commandsOut.push_back(command);
}

void ParticleRenderer::render_background(const ChunkMap<BiomeID> &biomeMarkers,
                                         const Assets &assets,
                                         BackgroundRenderSettings settings)
{
    const BiomeID *a = biomeMarkers.get(settings.worldPos);

    if (!a)
    {
        return;
    }

    const Texture *tex = nullptr;
    float amount = 0.0f;
    float rmult = 1.0f;
    float gmult = 1.0f;
    float bmult = 1.0f;
    switch (*a)
    {
    case BiomeID::DesertLayer1:
        tex = assets.textures().get(TextureID::SandBackground);
        amount = 0.0f;
        rmult = 0.4f;
        gmult = 0.36f;
        bmult = 0.26f;
        break;
    case BiomeID::DesertLayer2:
        tex = assets.textures().get(TextureID::SandBackground2);
        amount = 0.2f;
        rmult = 0.3f;
        gmult = 0.26f;
        bmult = 0.16f;
        break;
    default:
        break;
    }

    if (!tex)
    {
        return;
    }

    Vec2u size = tex->getSize();
    Vec2u parallax =
        calculate_parallax(settings.worldPos, settings.cameraPos, size, amount);

    Color c = tex->getPixel(parallax);

    c.r *= rmult;
    c.g *= gmult;
    c.b *= bmult;

    m_texture.setPixel(settings.drawPos, c);
}
