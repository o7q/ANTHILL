#include "dungeon_test_scene.hpp"

#include "core/math/triangle.hpp"
#include "core/viewport/render_command.hpp"

void DungeonTestScene::onStart() {}

void DungeonTestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    Vec2i mousePos = r_window.getViewport().windowToViewportPosition(r_window.getInput().getMousePosition());

    if (r_window.getInput().getInput(InputID::Shoot)->wasPressed())
    {
        m_points.push_back(mousePos);
        m_triangulated = Math::Triangle::generateTriangulation(m_points);
    }

    if (r_window.getInput().getInput(InputID::Jump)->wasPressed())
    {
    }

    PointsRenderCommandData pointsRenderData;
    pointsRenderData.points = m_points;
    pointsRenderData.color  = Color(255, 0, 0);
    renderCommands.push_back({0, pointsRenderData});

    for (const Triangle2i &tri : m_triangulated)
    {
        TriangleRenderCommandData triRenderData;
        triRenderData.vertices[0] = tri.verts[0];
        triRenderData.vertices[1] = tri.verts[1];
        triRenderData.vertices[2] = tri.verts[2];
        triRenderData.color       = Color(255, 255, 255);
        renderCommands.push_back({1, triRenderData});
    }

    r_window.getViewport().render(renderCommands);
}
