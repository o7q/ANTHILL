#include "dungeon_test_scene.hpp"

#include "core/math/rectangle.hpp"
#include "core/viewport/render_command.hpp"

void DungeonTestScene::onStart()
{
    // m_generator.generate();
    a.setPosition({100, 100});
    a.setSize({30, 20});
    b.setSize({10, 10});
}

void DungeonTestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    Vec2i mousePos = r_window.getViewport().windowToViewportPosition(r_window.getInput().getMousePosition());

    if (r_window.getInput().getInput(InputID::Shoot)->isDown())
    {
        m_generator.generate();
    }

    RectangleRenderCommandData boundsRenderData;
    boundsRenderData.a     = m_generator.getBounds().getA();
    boundsRenderData.b     = m_generator.getBounds().getB();
    boundsRenderData.color = Color(255, 0, 0);
    boundsRenderData.fill  = false;
    renderCommands.push_back({0, boundsRenderData});

    for (const GridRectangle &room : m_generator.getRooms())
    {
        RectangleRenderCommandData roomRenderData;
        roomRenderData.a     = room.getA();
        roomRenderData.b     = room.getB();
        roomRenderData.color = Color(255, 255, 0);
        roomRenderData.fill  = false;
        renderCommands.push_back({1, roomRenderData});
    }

    r_window.getViewport().render(renderCommands);
}
