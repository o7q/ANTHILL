#include "scene_main.hpp"

void MainScene::update_world()
{
    Vec2<float> player_pos = m_player.getPosition();
    m_world_update_bb = BoundingBox(player_pos.x, player_pos.y, 400, 500);
    m_wp_manager.update(player_pos);

    for (World *world : m_wp_manager.getWorldPartitions())
    {
        world->update(&m_world_update_bb);
    }
}

void MainScene::update_player()
{
    m_player.update();

    Vec2<float> player_pos = m_player.getPosition();
    m_camera.setGoal(player_pos.x, player_pos.y);
    m_camera.update(DT);
}

void MainScene::update_entities()
{
}