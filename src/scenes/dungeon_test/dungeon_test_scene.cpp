#include "dungeon_test_scene.hpp"

#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/triangle.hpp"
#include "core/math/mesh.hpp"
#include "core/viewport/render_command.hpp"

void DungeonTestScene::onStart() {}

void DungeonTestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    Vec2i mousePos = r_window.getViewport().windowToViewportPosition(r_window.getInput().getMousePosition());

    if (r_window.getInput().getInput(InputID::Shoot)->isDown())
    {
        m_generator.generate();
        m_rects = m_generator.getRooms();
        m_rects.push_back(m_generator.getBounds());

        std::vector<Vec2i> points;

        for (Rectangle_i rect : m_rects)
        {
            points.push_back(rect.getPosition());
        }
        m_triangulated = Math::Mesh::generateTriangulation(points);
    }

    for (const Rectangle_i &rect : m_rects)
    {
        RectangleRenderCommandData rectRenderData;
        rectRenderData.a     = rect.getA();
        rectRenderData.b     = rect.getB();
        rectRenderData.color = Color(255, 255, 255);
        renderCommands.push_back({0, rectRenderData});
    }

    for (const Triangle_i &tri : m_triangulated)
    {
        TriangleRenderCommandData triRenderData;
        triRenderData.vertices[0] = tri.verts[0];
        triRenderData.vertices[1] = tri.verts[1];
        triRenderData.vertices[2] = tri.verts[2];
        triRenderData.color       = Color(255, 255, 0);
        renderCommands.push_back({1, triRenderData});
    }

    r_window.getViewport().render(renderCommands);
}
