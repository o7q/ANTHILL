#include "bullet_manager.hpp"

void BulletManager::updateBullets(float dt)
{
    for (Bullet &bullet : m_bullets)
    {
        bullet.update(dt);
    }
}

std::vector<Bullet> BulletManager::checkWorld(World *world, float dt)
{
    return check_object(dt, [&](Bullet &bullet)
                        { return bullet.hitWorld(world, dt); });
}

std::vector<Bullet> BulletManager::checkBoundingBox(BoundingBox *boundingBox, float dt)
{
    return check_object(dt, [&](Bullet &bullet)
                        { return bullet.hitBoundingBox(boundingBox, dt); });
}

bool BulletManager::outOfBounds(Bullet bullet)
{
    return !m_kill_bb.pointInside(bullet.getPosition().x, bullet.getPosition().y);
}

void BulletManager::addBullet(Bullet bullet)
{
    m_bullets.push_back(bullet);
}

void BulletManager::addBulletRange(std::vector<Bullet> bullets)
{
    m_bullets.insert(m_bullets.end(), bullets.begin(), bullets.end());
}