#include "camera.hpp"

void Camera::update(float dt)
{
    if (std::abs(m_position.x - m_goal.x) < 0.25f)
    {
        m_position.x = m_goal.x;
    }
    else
    {
        m_position.x += (m_goal.x - m_position.x) * m_goalSpeed * dt;
    }
    if (std::abs(m_position.y - m_goal.y) < 0.25f)
    {
        m_position.y = m_goal.y;
    }
    else
    {
        m_position.y += (m_goal.y - m_position.y) * m_goalSpeed * dt;
    }
}
