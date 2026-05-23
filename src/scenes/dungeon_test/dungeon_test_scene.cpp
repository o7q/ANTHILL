#include "dungeon_test_scene.hpp"

#include "core/math/geometry/triangle.hpp"
#include "core/math/graph.hpp"
#include "core/math/mesh.hpp"
#include "core/viewport/render_command.hpp"
#include <vector>

void DungeonTestScene::onStart() {}

void DungeonTestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    Vec2i mousePos = r_window.getViewport().windowToViewportPosition(r_window.getInput().getMousePosition());

    if (r_window.getInput().getInput(InputID::Shoot)->wasPressed())
    {
        Node<Color> node;
        node.value = Color(255, 0, 0);
        m_triangulationGraph.set(mousePos, node);
    }
    if (r_window.getInput().getInput(InputID::Jump)->wasPressed())
    {
        std::vector<Vec2i> points;

        for (auto &[index, node] : m_triangulationGraph.getNodes())
        {
            points.push_back(index);
        }

        std::vector<Triangle_i> triangulation = Math::Mesh::generateTriangulation(points);
        Math::Graph::connectNodesFromTriangulation(triangulation, m_triangulationGraph);
        m_minimumTreeGraph = Math::Graph::minimumSpanningTree(m_triangulationGraph);
    }

    for (auto &[index, node] : m_triangulationGraph.getNodes())
    {
        CircleRenderCommandData pdata;
        pdata.pos    = index;
        pdata.radius = 2;
        pdata.color  = node.value;
        renderCommands.push_back({2, pdata});

        for (Vec2i connection : node.connections)
        {
            SegmentRenderCommandData sdata;
            sdata.a     = index;
            sdata.b     = connection;
            sdata.color = Color(10);
            renderCommands.push_back({0, sdata});
        }
    }

    for (auto &[index, node] : m_minimumTreeGraph.getNodes())
    {
        for (Vec2i connection : node.connections)
        {
            SegmentRenderCommandData sdata;
            sdata.a     = index;
            sdata.b     = connection;
            sdata.color = Color(255);
            renderCommands.push_back({1, sdata});
        }
    }

    r_window.getViewport().render(renderCommands);
}
