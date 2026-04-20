#include "camera.hpp"

void Camera::update(float dt)
{
    if (!m_goalSet)
    {
        return;
    }

    Vec2f move = (m_goal.toFloat().floor() - m_position.floor()) * 0.1f * dt;
    m_position += move;
}
