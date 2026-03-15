#include "camera.hpp"

Vec2<int> Camera::viewportToWorld(int x, int y, const Viewport &viewport) const
{
    return Vec2<int>(x, y) + m_position.toGrid() -
           viewport.getSize().toInt() / 2;
}

Vec2<int> Camera::worldToViewport(int x, int y, const Viewport &viewport) const
{
    return Vec2<int>(x, y) - m_position.toGrid() +
           viewport.getSize().toInt() / 2;
}
