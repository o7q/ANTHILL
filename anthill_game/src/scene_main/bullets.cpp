#include "scene_main.hpp"

void MainScene::update_bullets()
{
    m_bullet_manager.updateBullets(DT);

    for (World *world : m_world_manager.getWorlds())
    {
        for (const Bullet &bullet : m_bullet_manager.checkWorld(world, DT))
        {
            world->drawParticles(bullet.getPosition().x, bullet.getPosition().y, bullet.getPower(), Particle(), World::DrawShape::Circle, true);
        }
    }
}