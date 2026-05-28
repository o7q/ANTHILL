#include "particle_renderer.hpp"

#include "camera/camera.hpp"
#include "core/viewport/render_command.hpp"

void ParticleRenderer::render(const RenderData &data, std::vector<RenderCommand> &commandsOut)
{
    Vec2u size = data.camera.getViewSize();

    if (m_texture.getSize() != size)
    {
        reconstruct_texture(size);
    }

    for (unsigned int y = 0; y < size.y; ++y)
    {
        for (unsigned int x = 0; x < size.x; ++x)
        {
            m_texture.setPixel({x, y}, Color());

            Vec2i worldPos = data.camera.viewportToCamera(Vec2i(x, y));

            const Particle *p            = data.particles.get(worldPos);
            const Color *backgroundColor = data.background.get(worldPos);

            if (!p)
            {
                m_texture.setPixel({x, y}, Color(20, 0, 0));
            }
            else if (!p->isBlank())
            {
                m_texture.setPixel({x, y}, p->getColor());
            }
            else if (backgroundColor && backgroundColor->a != 0)
            {
                m_texture.setPixel({x, y}, *backgroundColor);
            }
            else
            {
                Vec2i cameraPos = data.camera.getPosition();
                render_biome(data.biomeMarkers, data.assets, worldPos, cameraPos, {x, y});
            }
        }
    }

    TextureRenderCommandData renderData;
    renderData.texture = &m_texture;
    renderData.origin  = {0, 0};

    RenderCommand command;
    command.index = 0;
    command.data  = renderData;

    commandsOut.push_back(command);
}

void ParticleRenderer::render_biome(const ChunkMap<BiomeID> &biomeMarkers, const Assets &assets,
                                    Vec2i worldPos, Vec2i cameraPos, Vec2u screenPos)
{
    const BiomeID *biomeMarker = biomeMarkers.get(worldPos);

    if (!biomeMarker)
    {
        return;
    }

    const Texture *texture = nullptr;
    float amount           = 0.0f;
    switch (*biomeMarker)
    {
    case BiomeID::DesertLayer1:
        texture = &assets.textures().get(TextureID::SandBackground);
        amount  = 0.0f;
        break;
    case BiomeID::DesertLayer2:
        texture = &assets.textures().get(TextureID::SandBackground);
        amount  = 0.2f;
        break;
    default:
        break;
    }

    if (!texture)
    {
        return;
    }

    Vec2u parallax = (worldPos.toFloat() - cameraPos.toFloat() * amount).toUnsignedInt() % texture->getSize();

    Color c = texture->getPixel(parallax);
    m_texture.setPixel(screenPos, c);
}
