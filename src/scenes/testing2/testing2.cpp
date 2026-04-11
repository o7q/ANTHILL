#include "testing2.hpp"
#include "backend/viewport/render_command.hpp"
#include "math/perlin.hpp"
#include "math/random.hpp"
#include "math/vec.hpp"
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
        
        int cellSize = 20;

        Vec2i mouseCellPos = viewportMousePos / cellSize;
        Index2D index = Index2D(mouseCellPos.x, mouseCellPos.y);

            

        if (m_seeds.find(index) != m_seeds.end())
        {
            m_seeds[index] = {Math::Random::weakRandInt(0, 100) / 100.0f,
                              Math::Random::weakRandInt(0, 100) / 100.0f};
        }

        for (unsigned int y = 0; y < m_screen.getSize().y; ++y)
        {
            for (unsigned int x = 0; x < m_screen.getSize().x; ++x)
            {
                Vec2i baseCell = Vec2i(x, y) / cellSize;

                float minDist = 10000000;

                for (int ry = -1; ry <= 1; ++ry)
                {
                    for (int rx = -1; rx <= 1; ++rx)
                    {
                        Vec2i cell = baseCell + Vec2i(rx, ry);

                        Vec2f cellPos =
                            cell.toFloat() + m_seeds[Index2D(cell.x, cell.y)];
                        cellPos *= cellSize;

                        float dx = cellPos.x - x;
                        float dy = cellPos.y - y;

                        float dist = std::sqrt(dx * dx + dy * dy);

                        if (dist < minDist)
                        {
                            minDist = dist;
                        }
                    }
                }

                Color c = Color(minDist * 8);

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
