#pragma once

#include <vector>

#include "../engine/math/bounding_box.hpp"
#include "../bullet/bullet.hpp"
#include "../world_manager/world_manager.hpp"

class BulletManager
{
public:
    void add(Bullet bullet) { m_bullets.push_back(bullet); }
    void update(const BoundingBox &bounds, float dt);

    void setWorldManager(WorldManager *world_manager) { m_world_manager = world_manager; }

    const std::vector<Bullet> &getBullets() const { return m_bullets; }
    const std::vector<Bullet> &getHitBullets() const { return m_hit_bullets; }

private:
    WorldManager *m_world_manager = nullptr;

    std::vector<Bullet> m_bullets;
    std::vector<Bullet> m_hit_bullets;
};