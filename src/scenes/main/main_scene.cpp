#include "main_scene.hpp"

#include "px/time/time_handler.hpp"
#include "px/window/render_command.hpp"

void MainScene::onStart()
{
    m_world.getEntityHandler().addPlayer(std::make_unique<Player>(r_instance.input(), r_assets));
    m_world.getEntityHandler().getCurrentPlayer()->getBody().setPosition({-50, -20});
    // r_window.getSound().playSound(r_assets.sounds().get(SoundID::MusicAction), {0.5f});
}

void MainScene::onTick()
{
    std::vector<px::RenderCommand> renderCommands;

    m_camera.setViewSize(r_instance.window().getViewportSize());

    px::Vec2i viewportMousePos =
        r_instance.window().windowToViewportPosition(r_instance.input().getMousePosition());
    px::Vec2f viewportMousePosCenterNormalized =
        (viewportMousePos - r_instance.window().getViewportSize().toInt() / 2).toFloat() /
        r_instance.window().getViewportSize().toFloat();

    px::Vec2i worldMousePos = m_camera.viewportToCamera(viewportMousePos);

    px::Vec2i updatePos;
    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        player->updateAimPosition(worldMousePos);
        updatePos = m_camera.getPosition();
    }

    m_generator.generate(updatePos.toInt(), {10, 10});
    m_world.update(r_instance.time().getInfo(), updatePos, m_events);

    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        m_camera.setGoal(player->getBody().getPosition() +
                         (viewportMousePosCenterNormalized * 60.0f).toGrid());
        m_camera.update(r_instance.time().getInfo());
    }

    m_world.render(m_camera, r_assets, renderCommands);

    renderText(renderCommands);

    handle_events();
    r_instance.window().renderCommandQueue(renderCommands);
}
