#include "particle_renderer.hpp"

void ParticleRenderer::render(Viewport &viewport, const Camera &camera,
                              const Assets &assets)
{
    Vec2u viewport_size = viewport.getSize();

    for (unsigned int y = 0; y < viewport_size.y; ++y)
    {
        for (unsigned int x = 0; x < viewport_size.x; ++x)
        {
            Vec2i cameraPos = camera.getPosition();
            Vec2i worldPos = camera.viewportToWorld(Vec2i(x, y), viewport);

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
                settings.viewportDrawPos = {x, y};
                render_background(viewport, assets, settings);
            }
            else
            {
                Color c = p->getColor();
                viewport.setPixel({x, y}, c);
            }
        }
    }
}

void ParticleRenderer::render_background(Viewport &viewport,
                                         const Assets &assets,
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

    viewport.setPixel(settings.viewportDrawPos, c);
}
