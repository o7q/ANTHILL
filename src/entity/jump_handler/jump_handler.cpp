#include "jump_handler.hpp"

void JumpHandler::update(float dt, bool onGround)
{
    m_jumped = false;

    if (onGround)
    {
        m_coyoteTimer.restart();
        m_allowCoyoteJump = true;
    }

    if (!onGround && m_jumpRequested)
    {
        m_bufferTimer.restart();
    }

    bool allowJump = false;

    if (onGround && m_jumpRequested)
    {
        allowJump         = true;
        m_allowCoyoteJump = false;
    }

    if (!onGround && m_jumpRequested)
    {
        if (m_allowCoyoteJump && m_coyoteTimer.active())
        {
            allowJump = true;
            m_coyoteTimer.stop();
        }
    }

    if (onGround && m_bufferTimer.active())
    {
        allowJump = true;
    }

    if (allowJump)
    {
        m_jumped = true;
        m_holdTimer.restart();
    }

    m_coyoteTimer.update(dt);
    m_holdTimer.update(dt);
    m_bufferTimer.update(dt);
    m_jumpRequested = false;
}
