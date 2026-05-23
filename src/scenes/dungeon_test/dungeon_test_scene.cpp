#include "dungeon_test_scene.hpp"

#include "core/math/geometry/rectangle.hpp"
#include "core/viewport/render_command.hpp"
#include <vector>

void DungeonTestScene::onStart() {}

void DungeonTestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    Rectangle_i bounds;
    bounds.setPosition({100, 100});
    bounds.setSize({200, 200});

    if (r_window.getInput().getInput(InputID::Shoot)->isDown())
    {
        m_roomGraph = m_generator.generate(bounds);
    }

    RectangleRenderCommandData boundsData;
    boundsData.a     = bounds.getA();
    boundsData.b     = bounds.getB();
    boundsData.color = Color(255, 0, 0);
    renderCommands.push_back({0, boundsData});

    for (auto &[index, node] : m_roomGraph.getNodes())
    {
        Rectangle_i rect(index, node.value);

        RectangleRenderCommandData rdata;
        rdata.a     = rect.getA();
        rdata.b     = rect.getB();
        rdata.color = Color(255, 255, 0);
        renderCommands.push_back({1, rdata});

        for (Vec2i connection : node.connections)
        {
            SegmentRenderCommandData sdata;
            sdata.a     = index;
            sdata.b     = connection;
            sdata.color = Color(255);
            renderCommands.push_back({0, sdata});
        }
    }

    r_window.getViewport().render(renderCommands);
}
