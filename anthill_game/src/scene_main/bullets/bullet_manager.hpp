#pragma once

#include <vector>
#include "../world_partitons/wp_manager.hpp"

#include "../../engine/math/bounding_box.hpp"

#include "../../bullet/bullet.hpp"
#include "../../player/player.hpp"

class BulletManager
{
public:
    BulletManager(const WPManager &wp_manager, const BoundingBox &bb) : m_wp_manager(wp_manager),
                                                                        m_bb(bb)
    {
    }

    void add(Bullet bullet)
    {
        m_bullets.push_back(bullet);
    }

    void update(float dt)
    {
        for (auto it = m_bullets.begin(); it != m_bullets.end();)
        {
            it->update(dt);

            bool bullet_hit = handle_oob_hit(it);

            if (!bullet_hit)
            {
                bullet_hit = handle_world_hit(it, dt);
            }

            it = bullet_hit ? m_bullets.erase(it) : ++it;
        }
    }

    const std::vector<Bullet> &getBullets() const { return m_bullets; }

private:
    bool handle_oob_hit(std::vector<Bullet>::iterator it)
    {
        Vec2<float> pos = it->getPosition();
        return !m_bb.pointInside(pos.x, pos.y);
    }

    bool handle_world_hit(std::vector<Bullet>::iterator it, float dt)
    {
        Vec2<float> pos = it->getPosition();

        bool bullet_hit = false;
        if (!m_bb.pointInside(pos.x, pos.y))
        {
            bullet_hit = true;
        }

        if (!bullet_hit)
        {
            for (World *world : m_wp_manager.getWorldPartitions())
            {
                if (world->getParticle(pos.x, pos.y).isSolidPassable())
                {
                    world->drawParticles(pos.x, pos.y, 2, Particle());
                }

                bool world_hit = it->checkWorldHit(world, dt);
                if (!world_hit)
                {
                    continue;
                }

                pos = it->getPosition();
                world->drawParticles(pos.x, pos.y, 5, Particle());

                bullet_hit = true;
                break;
            }
        }

        return bullet_hit;
    }

private:
    const WPManager &m_wp_manager;
    const BoundingBox &m_bb;

    std::vector<Bullet> m_bullets;
};