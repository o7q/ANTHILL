#pragma once

#include <vector>

#include "../bullet/bullet.hpp"

class BulletManager
{
public:
    BulletManager(BoundingBox &kill_bb) : m_kill_bb(kill_bb) {}

    void updateBullets(float dt);

    std::vector<Bullet> checkWorld(World *world, float dt);
    std::vector<Bullet> checkBoundingBox(BoundingBox *boundingBox, float dt);

    bool outOfBounds(Bullet bullet);

    void addBullet(Bullet bullet);
    void addBulletRange(std::vector<Bullet> bullets);

    const std::vector<Bullet> &getBullets() const { return m_bullets; }

private:
    template <typename T>
    std::vector<Bullet> check_object(float dt, T check)
    {
        std::vector<Bullet> hit_bullets;

        for (std::vector<Bullet>::iterator it = m_bullets.begin(); it != m_bullets.end();)
        {
            if (check(*it))
            {
                hit_bullets.push_back(*it);
            }

            bool hit = it->hit();
            bool out_of_bounds = outOfBounds(*it);

            if (hit || out_of_bounds)
            {
                m_bullets.erase(it);
            }
            else
            {
                ++it;
            }
        }

        return hit_bullets;
    }

private:
    std::vector<Bullet> m_bullets;
    BoundingBox &m_kill_bb;
};