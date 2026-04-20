#include "camera.hpp"

void Camera::update(float dt)
{
    if (!m_goalSet)
    {
        return;
    }

    Vec2f move = (m_goal.toFloat() - m_position) * 0.1f * dt;
    m_position += move;
}
