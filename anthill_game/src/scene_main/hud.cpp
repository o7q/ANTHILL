#include "scene_main.hpp"

void MainScene::handle_hud()
{
    Vec2<float> player_pos = m_player.getPosition();

    m_window.render().renderText(m_assets.fonts.alagard.font, std::to_string((int)FPS), Vec2<int>(1, m_window.getScale() - 15), Color(0, 255, 0, 255));
    m_window.render().renderText(m_assets.fonts.alagard.font, std::to_string(DT), Vec2<int>(30, m_window.getScale() - 15), Color(255, 255, 0, 255));
    m_window.render().renderText(m_assets.fonts.alagard.font, "X: " + std::to_string((int)player_pos.x) + "  Y: " + std::to_string((int)player_pos.y), Vec2<int>(100, m_window.getScale() - 15), Color(255, 0, 0, 255));

    if (m_window.input().isGamepadMode())
    {
        if (m_window.isCursorVisible())
        {
            Log::log(Log::Type::Info, "MainScene/hud", "Hiding cursor (gamepad mode enabled)");
            m_window.showCursor(false);
        }

        crosshair_texture->setPosition(m_aim_position.x, m_aim_position.y);
        m_window.render().renderTexture(*crosshair_texture, &m_camera);
    }
    else if (!m_window.isCursorVisible())
    {
        Log::log(Log::Type::Info, "MainScene/hud", "Showing cursor (gamepad mode disabled)");
        m_window.showCursor(true);
    }
}