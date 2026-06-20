#include "camera.hpp"

void Camera::update(px::TimeHandler::Info time)
{
    if (!m_goalSet)
    {
        return;
    }

    px::Vec2f diff = m_goal.toFloat().floor() - m_position.floor();

    m_position.x += diff.x * 0.1f * time.dt;
    m_position.y += diff.y * 0.1f * time.dt;

    int threshold = 29;

    if (diff.x > threshold)
    {
        m_position.x = m_goal.x - threshold;
    }
    else if (diff.x < -threshold)
    {
        m_position.x = m_goal.x + threshold;
    }
}
