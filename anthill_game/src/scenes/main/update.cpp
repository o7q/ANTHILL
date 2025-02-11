#include "scene_main.hpp"

void MainScene::handle_update()
{
    Vec2<float> player_pos = m_player.getPosition();
    m_update_bb = BoundingBox(player_pos.x, player_pos.y, 400, 600);

    for (World *world : m_world_partitons)
    {
        world->update(&m_update_bb);
    }

    m_player.update();

    m_camera.setGoal(player_pos.x, player_pos.y);
    m_camera.update(DT);
}