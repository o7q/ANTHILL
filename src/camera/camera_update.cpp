#include "camera.hpp"

void Camera::update(TimeHandler::Info time)
{
    if (!m_goalSet)
    {
        return;
    }

    Vec2f diff = m_goal.toFloat().floor() - m_position.floor();

    m_position.x += diff.x * 0.1f * time.dt;
    m_position.y += diff.y * 0.1f * time.dt;

    if (diff.x > 26)
    {
        m_position.x = m_goal.x - 26;
    }
    else if (diff.x < -26)
    {
        m_position.x = m_goal.x + 26;
    }
}
