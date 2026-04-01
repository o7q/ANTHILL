#include "jump_handler.hpp"
#include <iostream>

void JumpHandler::update(float dt, bool onGround)
{
    m_canJump = false;

    if (onGround)
    {
        m_coyoteTimer.restart();
    }

    if (!onGround && m_coyoteTimer.active() && m_jumpRequested)
    {
        m_canJump = true;
        m_coyoteTimer.stop();
    }

    if (onGround && m_jumpRequested)
    {
        m_canJump = true;
    }

    m_coyoteTimer.update(dt);
    m_jumpRequested = false;
}
