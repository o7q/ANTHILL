#include "scene_main.hpp"

void MainScene::handle_update()
{
    Vec2<float> player_pos = m_player.getPosition();
    m_world_update_bb = BoundingBox(player_pos.x, player_pos.y, 400, 500);

    for (World *world : m_wp_manager.getWorldPartitions())
    {
        world->update(&m_world_update_bb);
    }

    m_player.update();

    m_camera.setGoal(player_pos.x, player_pos.y);
    m_camera.update(DT);
}