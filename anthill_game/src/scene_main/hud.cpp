#include "scene_main.hpp"

void MainScene::update_hud()
{
    Vec2<float> player_pos = m_player.getPosition();

    m_window.render().renderText(m_assets.fonts.alagard, std::to_string((int)FPS), Vec2<int>(1, m_window.getScale() - 15), Color(0, 255, 0, 255));
    m_window.render().renderText(m_assets.fonts.alagard, std::to_string(DT), Vec2<int>(30, m_window.getScale() - 15), Color(255, 255, 0, 255));
    m_window.render().renderText(m_assets.fonts.alagard, "X: " + std::to_string((int)player_pos.x) + "  Y: " + std::to_string((int)player_pos.y), Vec2<int>(100, m_window.getScale() - 15), Color(255, 0, 0, 255));

    if (m_window.input().isGamepadMode())
    {
        if (m_window.isCursorVisible())
        {
            Log::log(Log::Level::Info, "MainScene/hud", "Hiding cursor (gamepad mode enabled)");
            m_window.showCursor(false);
        }

        Vec2<float> aim_position = m_player.getAimPosition();
        crosshair_texture->setPosition(aim_position.x, aim_position.y);
        m_window.render().renderTexture(crosshair_texture, &m_camera);
    }
    else if (!m_window.isCursorVisible())
    {
        Log::log(Log::Level::Info, "MainScene/hud", "Showing cursor (gamepad mode disabled)");
        m_window.showCursor(true);
    }
}