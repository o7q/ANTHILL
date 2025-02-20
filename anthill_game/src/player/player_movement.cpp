#include "player.hpp"

void Player::jump(bool override)
{
    // if we are in the range of a jump buffer
    // and we haven't already jump buffered: buffer the jump
    if (check_ground(m_jump_buffer_height) && !m_jump_buffered)
    {
        m_jump_buffered = true;
    }

    bool can_jump = false;

    if (m_on_ground)
    {
        can_jump = true;
    }

    // if we are not on the ground, and the coyote time exists, allow the jump
    if (!m_on_ground && m_coyote_time_timer >= 0.0f && !m_jumped)
    {
        ++m_jumps_left;
        can_jump = true;
    }

    if (m_jumps_left > 0)
    {
        can_jump = true;
    }

    if (!can_jump && !override)
    {
        return;
    }

    m_velocity.y = -m_jump_power;
    m_jump_buffered = false;
    m_jumped = true;

    --m_jumps_left;

    if (m_window.input().isGamepadMode())
    {
        m_window.input().rumbleGamepad(25000, 30000, 125);
    }
}

void Player::unjump()
{
    if (m_velocity.y <= 0.0f)
    {
        m_velocity.y /= m_unjump_amount;
    }
}