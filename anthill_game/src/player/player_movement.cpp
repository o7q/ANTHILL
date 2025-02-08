#include "player.hpp"

void Player::jump(bool override)
{
    if (check_ground(m_jump_buffer_height) && !m_jump_buffered)
    {
        m_jump_buffered = true;
    }

    if (!override)
    {
        if (!m_on_ground && m_coyote_time_timer <= 0.0f)
        {
            return;
        }
    }

    m_velocity.y = -m_jump_power;
    m_jump_buffered = false;
}