#include "scene_main.hpp"

void MainScene::handle_hud()
{
    Vec2<float> player_pos = m_player.getPosition();

    window.render().renderText(assets.fonts.alagard.font, std::to_string((int)FPS), Vec2<int>(1, window.getScale() - 15), Color(0, 255, 0, 255));
    window.render().renderText(assets.fonts.alagard.font, std::to_string(DT), Vec2<int>(30, window.getScale() - 15), Color(255, 255, 0, 255));
    window.render().renderText(assets.fonts.alagard.font, "X: " + std::to_string((int)player_pos.x) + "  Y: " + std::to_string((int)player_pos.y), Vec2<int>(100, window.getScale() - 15), Color(255, 0, 0, 255));

    if (window.input().isGamepadMode())
    {
        if (window.isCursorVisible())
        {
            Log::log(Log::Type::Info, "MainScene/hud", "Hiding cursor (gamepad mode enabled)");
            window.showCursor(false);
        }

        crosshair_texture->setPosition(m_aim_position.x, m_aim_position.y);
        window.render().renderTexture(*crosshair_texture, &m_camera);
    }
    else if (!window.isCursorVisible())
    {
        Log::log(Log::Type::Info, "MainScene/hud", "Showing cursor (gamepad mode disabled)");
        window.showCursor(true);
    }
}