#include "scene_main.hpp"

void MainScene::update_bullets()
{
    for (std::vector<Bullet>::iterator it = m_bullets.begin(); it != m_bullets.end();)
    {
        it->update(DT);

        for (World *world : m_world_manager.getWorlds())
        {
            if (it->hitWorld(world, DT))
            {
                world->drawParticles(it->getPosition().x, it->getPosition().y, it->getPower(), Particle(), World::DrawShape::Circle, true);
            }
        }

        bool hit = it->hit();
        bool out_of_bounds = !m_world_update_bb.pointInside(it->getPosition().x, it->getPosition().y);

        if (hit || out_of_bounds)
        {
            m_bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}