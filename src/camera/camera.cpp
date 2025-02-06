#include "camera.hpp"

void Camera::setPosition(int x, int y)
{
    m_position.x = x;
    m_position.y = y;
}

void Camera::move(int x, int y)
{
    m_position.x += x;
    m_position.y += y;
}

Vec2<int> Camera::transformPoint(Vec2<int> point) const
{
    return point + m_position;
}

Vec2<int> Camera::transformPoint(int x, int y) const
{
    return Vec2<int>(x + m_position.x, y + m_position.y);
}