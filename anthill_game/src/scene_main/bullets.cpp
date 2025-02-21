#include "scene_main.hpp"

void MainScene::update_bullets()
{
    for (World *world : m_world_manager.getWorlds())
    {
        for (Bullet bullet : m_bullet_manager.checkWorld(world, DT))
        {
            world->drawParticles(bullet.getPosition().x, bullet.getPosition().y, bullet.getPower(), Particle(), World::DrawShape::Circle, true);
        }
    }
}