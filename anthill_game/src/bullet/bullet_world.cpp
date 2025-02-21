#include "bullet.hpp"

#include "../engine/math/segment.hpp"

bool Bullet::hitWorld(World *world, float dt)
{
    if (m_hit)
    {
        return false;
    }

    Particle p = world->getParticle(m_position.x, m_position.y);
    if (p.p_collision_type == Particle::PCollisionType::Solid && p.solid_enable_collision)
    {
        m_hit = true;
        return true;
    }

    Vec2<float> future_position = m_position + Vec2<float>(m_dx, m_dy) * m_speed * dt;
    Segment bullet_trajectory(m_position, future_position);

    for (const Segment &segment : world->getWorldHitbox())
    {
        Segment::IData i_data = bullet_trajectory.segmentIntersect(segment);
        if (i_data.intersecting)
        {
            m_position = i_data.position;

            m_hit = true;
            return true;
        }
    }

    return false;
}