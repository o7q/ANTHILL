#include "world_physics.hpp"

bool WorldPhysics::in_bounds(int x, int y)
{
    bool y_can_up    = (y >= 0)       || (m_portal.up    != nullptr);
    bool y_can_down  = (y < m_size.y) || (m_portal.down  != nullptr);
    bool x_can_left  = (x >= 0)       || (m_portal.left  != nullptr);
    bool x_can_right = (x < m_size.x) || (m_portal.right != nullptr);

    return y_can_up && y_can_down && x_can_left && x_can_right;
}

void WorldPhysics::setPortal(Portal portal)
{
    m_portal = portal;
}

void WorldPhysics::setWorldTexture(Texture *world_texture)
{
    m_world_texture = world_texture;
}