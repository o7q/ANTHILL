#include "testing2.hpp"
#include "backend/viewport/render_command.hpp"
#include "math/color.hpp"
#include "math/interpolation.hpp"
#include "math/perlin.hpp"
#include "math/random.hpp"
#include "math/vec.hpp"
#include "math/voronoi.hpp"
#include <vector>

void TestScene2::onStart() {}

void TestScene2::onTick()
{
    std::vector<RenderCommand> renderCommands;

    if (r_input.getInput(InputID::Action1)->isDown())
    {
        m_screen.clear();

        Vec2i gridSize = {20, 20};

        Color colors[3] = {Color(255, 0, 0), Color(0, 255, 0),
                           Color(0, 0, 255)};

        int seed = Math::Random::weakRandInt(0, 200);

        for (unsigned int y = 0; y < m_screen.getSize().y; ++y)
        {
            for (unsigned int x = 0; x < m_screen.getSize().x; ++x)
            {
                float p = Math::Perlin::sampleEx(Vec2f(x, y), {20, 20}, 1, seed) - 0.5f;

                p *= Math::Interpolation::easeOutCubic(0, 20, y / (float)m_screen.getSize().y);

                Math::Voronoi::Sample sample = Math::Voronoi::sampleEx(
                    Vec2f(x + p * 200, y + p * 200), gridSize.toFloat(), seed);

                Color c = colors[Math::Random::hashFromPosition(sample.cell, seed) % 3];

                m_screen.setPixel({x, y}, c);
            }
        }
    }

    TextureRenderCommandData data;
    data.texture = &m_screen;
    data.origin = {0, 0};

    renderCommands.push_back({0, data});

    r_viewport.render(renderCommands);
}
