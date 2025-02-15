#include "camera.hpp"

Vec2<float> Camera::windowToGame(float x, float y) const
{
    return Vec2<float>(x + m_position.x - m_window_size.x / 2.0f, y + m_position.y - m_window_size.y / 2.0f);
}