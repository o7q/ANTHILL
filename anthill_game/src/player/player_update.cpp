#include "player.hpp"

void Player::update()
{
    m_on_ground = false;
    m_on_ground = check_ground(1);

    float dt = m_window.time().getDeltaTime();

    // if we are on the ground, and our jump was buffered, jump
    if (m_on_ground && m_jump_buffered)
    {
        jump(true);
    }

    // if we are on the ground, reset our coyote timer
    // we we're not, dimish the timer
    if (m_on_ground)
    {
        m_coyote_time_timer = m_coyote_time;
    }
    else
    {
        m_coyote_time_timer -= 1.0f * dt;
    }

    update_x_velocity();
    update_y_velocity();

    move(m_velocity.x * dt, m_velocity.y * dt);

    resolve_world_collision();
}