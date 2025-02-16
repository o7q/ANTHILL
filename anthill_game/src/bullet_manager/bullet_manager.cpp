#include "bullet_manager.hpp"

void BulletManager::update(const BoundingBox &bounds, float dt)
{
    m_hit_bullets.clear();

    for (std::vector<Bullet>::iterator it = m_bullets.begin(); it != m_bullets.end();)
    {
        it->update(dt);

        Vec2<float> pos = it->getPosition();
        bool out_of_bounds = !bounds.pointInside(pos.x, pos.y);

        if (m_world_manager != nullptr)
        {
            for (World *world : m_world_manager->getWorlds())
            {
                it->checkWorld(world, dt);
            }
        }

        bool hit = it->hit();

        if (hit)
        {
            Bullet hit_bullet = *it;
            m_hit_bullets.push_back(hit_bullet);
        }

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