#include "bb_world_collider.hpp"

void BBWorldCollider::resolve(const World *world)
{
    m_bb_pos = m_bb.getPosition().toInt();
    m_bb_size = m_bb.getSize().toInt();
    m_resolve = Vec2<int>(0, 0);

    convex_optimize(world);
}