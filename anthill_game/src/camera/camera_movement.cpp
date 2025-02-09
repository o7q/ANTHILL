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