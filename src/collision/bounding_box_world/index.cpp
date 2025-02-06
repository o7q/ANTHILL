#include "bb_world_resolver.hpp"

int BBWorldResolver::i_x(int x)
{
    return m_bb_size.x - 1 - x;
}
int BBWorldResolver::i_y(int y)
{
    return m_bb_size.y - 1 - y;
}