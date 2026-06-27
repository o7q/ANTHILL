#include "particle_renderer.hpp"

#include "camera/camera.hpp"
#include "px/canvas/draw_types.hpp"

void ParticleRenderer::render(const RenderData &data, std::vector<px::DrawCommand> &commandsOut)
{
    px::Vec2u size = data.camera.getViewSize();

    if (m_texture.getSize() != size)
    {
        reconstruct_texture(size);
    }

    for (unsigned int y = 0; y < size.y; ++y)
    {
        for (unsigned int x = 0; x < size.x; ++x)
        {
            m_texture.setPixel({x, y}, {0, 0, 0, 255});

            px::Vec2i worldPos = data.camera.viewportToCamera(px::Vec2u{x, y}.toInt());

            const Particle *p                = data.particles.get(worldPos);
            const px::Color *backgroundColor = data.background.get(worldPos);

            if (!p)
            {
                m_texture.setPixel({x, y}, px::Color(20, 0, 0));
            }
            else if (p->getColor().a != 0)
            {
                m_texture.setPixel({x, y}, p->getColor());
            }
            else if (backgroundColor && backgroundColor->a != 0)
            {
                m_texture.setPixel({x, y}, *backgroundColor);
            }
            else
            {
                px::Vec2i cameraPos = data.camera.getPosition();
                render_biome(data.biomeMarkers, data.assets, worldPos, cameraPos, {x, y});
            }
        }
    }

    px::TextureDrawConfig renderData;
    renderData.texture = &m_texture;
    renderData.origin  = {0, 0};

    px::DrawCommand command;
    command.index = 0;
    command.data  = renderData;

    commandsOut.push_back(command);
}

void ParticleRenderer::render_biome(const px::ChunkMap<BiomeID> &biomeMarkers, const Assets &assets,
                                    px::Vec2i worldPos, px::Vec2i cameraPos, px::Vec2u screenPos)
{
    const BiomeID *biomeMarker = biomeMarkers.get(worldPos);

    if (!biomeMarker)
    {
        return;
    }

    const px::Texture *texture = nullptr;
    float amount               = 0.0f;
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

    px::Vec2u parallax =
        (worldPos.toFloat() - cameraPos.toFloat() * amount).toUnsignedInt() % texture->getSize();

    px::Color c = texture->getPixel(parallax);
    m_texture.setPixel(screenPos, c);
}
