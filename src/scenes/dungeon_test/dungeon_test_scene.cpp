#include "dungeon_test_scene.hpp"

#include "core/math/geometry/triangle.hpp"
#include "core/math/mesh.hpp"
#include "core/viewport/render_command.hpp"

void DungeonTestScene::onStart() {}

void DungeonTestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    Vec2i mousePos = r_window.getViewport().windowToViewportPosition(r_window.getInput().getMousePosition());

    if (r_window.getInput().getInput(InputID::Shoot)->wasPressed())
    {
        m_points.push_back(mousePos);
        m_triangulation = Math::Mesh::generateTriangulation(m_points);
    }

    for (Triangle_i tri : m_triangulation)
    {
        TriangleRenderCommandData triData;
        triData.vertices[0] = tri.verts[0];
        triData.vertices[1] = tri.verts[1];
        triData.vertices[2] = tri.verts[2];
        triData.color       = Color(255);
        renderCommands.push_back({0, triData});
    }

    r_window.getViewport().render(renderCommands);
}
