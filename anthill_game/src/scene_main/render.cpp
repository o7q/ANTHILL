#include "scene_main.hpp"

void MainScene::handle_render()
{
    for (World *world : m_wp_manager.getWorldPartitions())
    {
        m_window.render().renderTexture(world->getWorldTexture(), &m_camera);
    }

    m_window.render().debug_renderBoundingBox(m_player.getBoundingBox(), Color(0, 255, 100, 255), &m_camera);
    m_window.render().debug_renderBoundingBox(m_world_update_bb, Color(255, 0, 0, 255), &m_camera);
}