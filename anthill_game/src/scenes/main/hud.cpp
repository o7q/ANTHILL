#include "scene_main.hpp"

void MainScene::handle_hud()
{
    Vec2<float> player_pos = m_player.getPosition();

    window.render().renderText(assets.fonts.alagard.font, std::to_string((int)FPS), Vec2<int>(1, window.getScale() - 15), Color(0, 255, 0, 255));
    window.render().renderText(assets.fonts.alagard.font, std::to_string(DT), Vec2<int>(30, window.getScale() - 15), Color(255, 255, 0, 255));
    window.render().renderText(assets.fonts.alagard.font, "X: " + std::to_string((int)player_pos.x) + "  Y: " + std::to_string((int)player_pos.y), Vec2<int>(100, window.getScale() - 15), Color(255, 0, 0, 255));
}