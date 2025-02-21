#include "bullet.hpp"

bool Bullet::hitBoundingBox(BoundingBox *bb, float dt)
{
    if (m_hit)
    {
        return false;
    }

    if (bb->pointInside(m_position.x, m_position.y))
    {
        m_hit = true;
        return true;
    }

    Vec2<float> p[4] = {bb->getP1(), bb->getP2(), bb->getP3(), bb->getP4()};

    Vec2<float> future_position = m_position + Vec2<float>(m_dx, m_dy) * m_speed * dt;
    Segment bullet_trajectory(m_position, future_position);

    for (int i = 0; i < 4; ++i)
    {
        Segment bb_side(p[i % 4], p[(i + 1) % 4]);

        if (bullet_trajectory.segmentIntersect(bb_side).intersecting)
        {
            m_hit = true;
            return true;
        }
    }

    return false;
}