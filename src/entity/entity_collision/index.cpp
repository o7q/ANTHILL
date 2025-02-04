#include "entity_collision.hpp"

int EntityCollision::inverse_x(int x)
{
    return m_entity_bounds.x - 1 - x;
}
int EntityCollision::inverse_y(int y)
{
    return m_entity_bounds.y - 1 - y;
}