#include "testing2.hpp"
#include "backend/viewport/render_command.hpp"
#include "math/color.hpp"
#include "math/perlin.hpp"
#include "math/random.hpp"
#include "math/vec.hpp"
#include "math/voronoi.hpp"
#include "utils/data_structures/index_2d.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

void TestScene2::onStart() {}

void TestScene2::onTick()
{
    std::vector<RenderCommand> renderCommands;

    Vec2i viewportMousePos =
        r_viewport.windowToViewportPosition(r_input.getMousePosition());

    if (r_input.getInput(InputID::Action1)->isDown())
    {
        m_screen.clear();

        Vec2i gridSize = {20, 20};

        Vec2i mouseCellPos = viewportMousePos / gridSize;
        Index2D index = Index2D(mouseCellPos.x, mouseCellPos.y);

        Color colors[3] = {Color(255, 0, 0), Color(0, 255, 0),
                           Color(0, 0, 255)};

        Math::Voronoi::VoronoiSeed<Color> seed;
        seed.data = colors[Math::Random::weakRandInt(0, 3)];
        seed.localPosition = {Math::Random::weakRandInt(0, 100) / 100.0f,
                              Math::Random::weakRandInt(0, 100) / 100.0f};

        m_seeds[index] = seed;

        for (unsigned int y = 0; y < m_screen.getSize().y; ++y)
        {
            for (unsigned int x = 0; x < m_screen.getSize().x; ++x)
            {
                float vx = Math::Perlin::sampleEx(Vec2f(x, y),
                                                  gridSize.toFloat(), 1, 0)-0.5f;
                float vy = Math::Perlin::sampleEx(Vec2f(x, y),
                                                  gridSize.toFloat(), 1, 0)-0.5f;



                Math::Voronoi::VoronoiSample sample =
                    Math::Voronoi::sampleEx<Color>(Vec2f(x + vx*100, y + vy*100),
                                                   gridSize.toFloat(), m_seeds);

                if (m_seeds.find(sample.index) == m_seeds.end())
                {
                    continue;
                }

                Math::Voronoi::VoronoiSeed<Color> s = m_seeds.at(sample.index);

                m_screen.setPixel({x, y}, s.data);
            }
        }
    }

    TextureRenderCommandData data;
    data.texture = &m_screen;
    data.origin = {0, 0};

    renderCommands.push_back({0, data});

    r_viewport.render(renderCommands);
}
