#include "scene_main.hpp"

void MainScene::update_render()
{
    for (World *world : m_world_manager.getWorlds())
    {
        m_window.render().renderTexture(world->getWorldTexture(), &m_camera);
    }

    m_window.render().debug_renderBoundingBox(m_player.getBoundingBox(), Color(0, 255, 100, 255), &m_camera);
    m_window.render().debug_renderBoundingBox(m_world_update_bb, Color(255, 0, 0, 255), &m_camera);

    for (const Bullet &bullet : m_bullets)
    {
        m_window.render().debug_renderPoint(bullet.getPosition().x, bullet.getPosition().y, Color(255, 255, 0, 255), &m_camera);
    }
}