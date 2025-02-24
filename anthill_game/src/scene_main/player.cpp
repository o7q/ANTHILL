#include "scene_main.hpp"

void MainScene::update_player()
{
    m_player.update();

    Vec2<float> player_pos = m_player.getPosition();
    m_update_bb = BoundingBox(player_pos.x, player_pos.y, 576, 448);

    m_camera.setGoal(player_pos.x, player_pos.y);
    m_camera.update(DT);

    if (player_pos.y > m_world_manager.getVerticalPos() - 2000 && m_can_gen_next)
    {
        WorldGenerator::Settings wgs{2000, 2000, -1, WorldGenerator::Settings::Preset::Jungle};
        m_world_manager.queue(wgs);
        m_world_manager.queue(wgs);
        m_world_manager.queue(wgs);
        m_world_manager.queue(wgs);
        m_can_gen_next = false;
    }
    else if (m_world_manager.queueFinished())
    {
        m_can_gen_next = true;
    }
}