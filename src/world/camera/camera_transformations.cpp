#include "camera.hpp"

Vec2i Camera::viewportToWorld(int x, int y, const Viewport &viewport) const
{
    return Vec2i(x, y) + m_position.toGrid() - viewport.getSize().toInt() / 2;
}

Vec2i Camera::worldToViewport(int x, int y, const Viewport &viewport) const
{
    return Vec2i(x, y) - m_position.toGrid() + viewport.getSize().toInt() / 2;
}
