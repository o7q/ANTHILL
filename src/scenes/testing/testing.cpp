#include "testing.hpp"
#include "backend/viewport/render_command.hpp"
#include "entities/wuskkogel/wuskkogel.hpp"
#include <memory>

void TestScene::onStart()
{
    m_world.getEntityHandler().addPlayer(std::make_unique<Player>(
        m_world.getEntityHandler().getIDHandler().getNext(), r_input,
        r_assets));

    m_world.getEntityHandler().getCurrentPlayer()->getBody().setPosition(
        {0, -200});

    auto wuskkogel = std::make_unique<Wuskkogel>(
        m_world.getEntityHandler().getIDHandler().getNext(), r_assets);
    wuskkogel->getBody().setPosition({0, -20});
    m_world.getEntityHandler().addEntity(std::move(wuskkogel));
}

void TestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    m_camera.setViewSize(r_viewport.getSize());

    Vec2i viewportMousePos =
        r_viewport.windowToViewportPosition(r_input.getMousePosition());
    Vec2i worldMousePos = m_camera.viewportToCamera(viewportMousePos);

    Player *player = m_world.getEntityHandler().getCurrentPlayer();
    player->updateAimPosition(worldMousePos);

    Vec2i playerPos = player->getBody().getPosition();
    m_world.getGenerator().generateInRadius(playerPos.toInt(), {4, 4});
    m_camera.setGoal(playerPos);
    m_camera.update(r_time.getDT());

    m_world.update(r_time.getDT(), playerPos, m_backendEvents);
    m_world.render(m_camera, r_assets, renderCommands);

    fpsText = r_assets.fonts()
                  .get(FontID::Default)
                  ->generateStringTexture(std::to_string((int)r_time.getFPS()),
                                          Color(0, 255, 0), 5, 1, 8);

    TextureRenderCommandData fpsRenderData;
    fpsRenderData.texture = &fpsText;
    fpsRenderData.position = {10, 5};

    RenderCommand fpsRenderCommand;
    fpsRenderCommand.data = fpsRenderData;
    renderCommands.push_back(fpsRenderCommand);

    r_viewport.render(renderCommands);
}
