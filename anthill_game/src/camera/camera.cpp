#include "camera.hpp"

Vec2<int> Camera::transformPoint(float x, float y) const
{
    return Vec2<int>(x + m_position.x - m_window_size.x / 2.0f, y + m_position.y - m_window_size.x / 2.0f);
}