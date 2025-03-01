#include "scene_main.hpp"

void MainScene::update_world()
{
    m_world_manager.updateQueue();

    for (World *world : m_world_manager.getWorlds())
    {
        if (m_player.dashing())
        {
            world->drawParticles(m_player.getPosition().x, m_player.getPosition().y, 15, Particle(), World::DrawShape::Circle, true);
        }
        world->update(&m_update_bb);
    }
}