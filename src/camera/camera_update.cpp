#include "camera.hpp"
#include <iostream>

void Camera::update(float dt)
{
    if (!m_goalSet)
    {
        return;
    }

    m_position += (m_goal.toFloat().floor() - m_position.floor()) * 0.05f * dt;

    Vec2f diff = m_goal.toFloat() - m_position;

    if (diff.x > 20)
    {
        m_position.x = m_goal.x - 20;
    }
    else if (diff.x < -20)
    {
        m_position.x = m_goal.x + 20;
    }
}
