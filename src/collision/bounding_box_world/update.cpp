#include "bb_world_collider.hpp"

void BBWorldCollider::update()
{
    m_bb_pos = m_bb.getPosition();
    m_bb_size = m_bb.getSize();
    convex_optimize();
}