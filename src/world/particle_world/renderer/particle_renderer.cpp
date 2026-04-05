#include "particle_renderer.hpp"
#include "backend/viewport/render_command.hpp"
#include "camera/camera.hpp"

void ParticleRenderer::render(const Camera &camera, const Assets &assets,
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

            Particle *p = r_particles.get(worldPos);

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
                render_background(assets, settings);
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

void ParticleRenderer::render_background(const Assets &assets,
                                         BackgroundRenderSettings settings)
{
    const Texture *sand = assets.textures().get(TextureID::SandBackground);

    Vec2u size = sand->getSize();
    Vec2u parallax =
        calculate_parallax(settings.worldPos, settings.cameraPos, size, 0.2f);

    Color c = sand->getPixel(parallax);

    c.r *= 0.3f;
    c.g *= 0.26f;
    c.b *= 0.16f;

    m_texture.setPixel(settings.drawPos, c);
}
