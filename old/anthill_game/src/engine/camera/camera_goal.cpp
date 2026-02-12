#include "camera.hpp"

void Camera::setGoal(float x, float y)
{
    m_goal_position.x = x;
    m_goal_position.y = y;
    m_has_goal = true;
}

void Camera::update_goal(float dt)
{
    if (!m_has_goal)
    {
        return;
    }

    float speed_damp = m_goal_speed * dt;
    float x_offset = m_goal_position.x - m_position.x;
    float y_offset = m_goal_position.y - m_position.y;

    move(x_offset * speed_damp, y_offset * speed_damp);

    if (x_offset * x_offset + y_offset * y_offset <= 1.0f)
    {
        m_has_goal = false;
    }
}