#include "camera.hpp"

Vec2i Camera::viewportToCamera(Vec2i pos) const
{
    return pos + m_position.toGrid() - m_viewSize.toInt() / 2;
}

Vec2i Camera::cameraToViewport(Vec2i pos) const
{
    return pos - m_position.toGrid() + m_viewSize.toInt() / 2;
}
