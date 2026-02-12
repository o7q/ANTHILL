#include "player.hpp"

void Player::update()
{
    float dt = m_window.time().getDeltaTime();
    
    m_on_ground = check_ground(1);
    m_speed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

    if (m_weapon != nullptr)
    {
        m_weapon->setAimPosition(m_aim_position.x, m_aim_position.y);
    }

    // if we are on the ground, and our jump was buffered, jump
    if (m_on_ground && m_jump_buffered)
    {
        jump(true);
    }

    // if we are on the ground, reset our coyote timer
    // we we're not, dimish the timer
    if (m_on_ground)
    {
        m_jumps_left = m_extra_jumps;
        m_coyote_time_timer = m_coyote_time;
    }
    else
    {
        m_coyote_time_timer -= 1.0f * dt;
    }

    if (m_coyote_time_timer <= 0.0f)
    {
        m_jumped = false;
    }

    update_x_velocity();
    update_y_velocity();

    if (m_dash_timer > 0.0f)
    {
        m_dash_timer -= 1.0f * dt;
        m_velocity.x = m_dash_vector.x;
        m_velocity.y = m_dash_vector.y;
    }
    else if (m_speed < 8.0f)
    {
        m_dashing = false;
    }

    move(m_velocity.x * dt, m_velocity.y * dt);

    if (!m_dashing)
    {
        resolve_world_collision();
    }
}