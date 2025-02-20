#include "player.hpp"

void Player::update_x_velocity()
{
    float dt = m_window.time().getDeltaTime();
    float air_resistance_factor = std::exp(-dt * m_air_resistance);
    m_velocity.x *= air_resistance_factor;

    if (std::fabs(m_velocity.x) < 0.25f)
    {
        m_velocity.x = 0.0f;
    }
}

void Player::update_y_velocity()
{
    if (!m_is_gravity_affected)
    {
        return;
    }

    float dt = m_window.time().getDeltaTime();
    if (m_velocity.y < m_terminal_velocity)
    {
        float fast_fall = 1.0f;
        if (m_velocity.y > 0.0f)
            fast_fall = 1.5f;

        m_velocity.y += m_gravity_strength * fast_fall * dt;
    }

    if (m_on_ground && m_velocity.y > 0)
    {
        m_velocity.y = 0;
    }
}