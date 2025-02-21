#include "scene_main.hpp"

void MainScene::update_player()
{
    m_player.update();

    Vec2<float> player_pos = m_player.getPosition();
    m_update_bb = BoundingBox(player_pos.x, player_pos.y, 576, 448);

    m_camera.setGoal(player_pos.x, player_pos.y);
    m_camera.update(DT);
}