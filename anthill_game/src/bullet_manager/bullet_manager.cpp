#include "bullet_manager.hpp"

void BulletManager::update(const BoundingBox &bounds, float dt)
{
    m_hit_bullets.clear();

    for (std::vector<Bullet>::iterator it = m_bullets.begin(); it != m_bullets.end();)
    {
        it->update(dt);

        Vec2<float> b_pos = it->getPosition();
        bool out_of_bounds = !bounds.pointInside(b_pos.x, b_pos.y);

        if (m_world_manager != nullptr)
        {
            for (World *world : m_world_manager->getWorldPartitions())
            {
                it->checkWorld(world, dt);
            }
        }

        if (it->hit())
        {
            Bullet hit_bullet = *it;
            m_hit_bullets.push_back(hit_bullet);
        }

        if (it->hit() || out_of_bounds)
        {
            m_bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}