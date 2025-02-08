#include "camera.hpp"

void Camera::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

void Camera::move(float x, float y)
{
    m_position.x += x;
    m_position.y += y;
}

Vec2<int> Camera::transformPoint(float x, float y) const
{
    return Vec2<int>(x + m_position.x, y + m_position.y);
}