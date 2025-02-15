#include "bb_world_collider.hpp"

int BBWorldCollider::i_x(int x)
{
    return m_bb_size.x - 1 - x;
}
int BBWorldCollider::i_y(int y)
{
    return m_bb_size.y - 1 - y;
}