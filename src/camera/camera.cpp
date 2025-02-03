#include "camera.hpp"

void Camera::setPosition(Vec2<float> position)
{
    m_position = position;
}

void Camera::move(float x, float y)
{
    m_position.x += x;
    m_position.y += y;
}

Vec2<float> Camera::transformPoint(Vec2<float> point) const
{
    return point + m_position;
}

Vec2<float> Camera::transformPoint(float x, float y) const
{
    return Vec2<float>(x + m_position.x, y + m_position.y);
}