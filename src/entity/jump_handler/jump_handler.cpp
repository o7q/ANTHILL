#include "jump_handler.hpp"

void JumpHandler::update(float dt, bool onGround)
{
    if (onGround)
    {
        m_coyoteTimer.restart();
        m_allowCoyoteJump = true;
        m_doubleJumpCounter = 0;
    }

    if (onGround && m_jumpRequested)
    {
        m_holdJumpTimer.restart();
        m_allowCoyoteJump = false;
    }

    if (!onGround && m_jumpRequested)
    {
        bool coyoteJumped = false;
        if (m_allowCoyoteJump && m_coyoteTimer.active())
        {
            m_holdJumpTimer.restart();
            m_coyoteTimer.stop();
            coyoteJumped = true;
        }

        if (m_doubleJumpCounter < m_doubleJumpAmount && !coyoteJumped)
        {
            m_holdJumpTimer.restart();
            m_doubleJumpCounter++;
        }
    }

    m_coyoteTimer.update(dt);
    m_holdJumpTimer.update(dt);
    m_jumpRequested = false;
}
