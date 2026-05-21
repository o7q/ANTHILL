#include "dungeon_test_scene.hpp"

#include "core/math/delaunay.hpp"
#include "core/math/line.hpp"
#include "core/math/triangle.hpp"
#include "core/viewport/render_command.hpp"
#include <iostream>

void DungeonTestScene::onStart() {}

void DungeonTestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    Vec2i mousePos = r_window.getViewport().windowToViewportPosition(r_window.getInput().getMousePosition());

    // if (r_window.getInput().getInput(InputID::Shoot)->wasPressed())
    // {
    //     m_points.push_back(mousePos);
    // }

    // if (r_window.getInput().getInput(InputID::Jump)->wasPressed())
    // {
    //     m_triangulated = generateDelaunayTriangle(m_points);
    // }

    // PointsRenderCommandData pointsRenderData;
    // pointsRenderData.points = m_points;
    // pointsRenderData.color  = Color(255, 0, 0);
    // renderCommands.push_back({0, pointsRenderData});

    // for (const Tri2i &tri : m_triangulated)
    // {
    //     TriangleRenderCommandData triRenderData;
    //     triRenderData.tri   = tri;
    //     triRenderData.color = Color(255, 255, 255);
    //     renderCommands.push_back({1, triRenderData});
    // }

    Triangle2i tri;
    tri.setVertices({50, 50}, {100, 20}, mousePos);

    Circle2f circ = tri.calculateCircumcircle();

    TriangleRenderCommandData triData;
    triData.v0    = tri.getV0();
    triData.v1    = tri.getV1();
    triData.v2    = tri.getV2();
    triData.color = Color(255, 0, 0);
    renderCommands.push_back({1, triData});

    CircleRenderCommandData circData;
    circData.pos    = circ.pos.toGrid();
    circData.radius = static_cast<int>(std::floor(circ.radius));
    circData.color  = Color(255, 255, 255);
    renderCommands.push_back({0, circData});

    r_window.getViewport().render(renderCommands);
}
