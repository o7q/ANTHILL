#include "camera.hpp"

Vec2<int> Camera::viewportToWorld(int x, int y, const Viewport &viewport) const
{
    return (Vec2<float>(x, y) + m_position -
            viewport.getSize().toFloat() / 2.0f)
        .toGrid();
}

Vec2<int> Camera::worldToViewport(int x, int y, const Viewport &viewport) const
{
    return (Vec2<float>(x, y) - m_position +
            viewport.getSize().toFloat() / 2.0f)
        .toGrid();
}
