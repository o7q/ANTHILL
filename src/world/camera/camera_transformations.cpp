#include "camera.hpp"

Vec2i Camera::viewportToWorld(Vec2i pos, const Viewport &viewport) const
{
    return pos + m_position.toGrid() - viewport.getSize().toInt() / 2;
}

Vec2i Camera::worldToViewport(Vec2i pos, const Viewport &viewport) const
{
    return pos - m_position.toGrid() + viewport.getSize().toInt() / 2;
}
