#include "entity_jump_module.hpp"
#include <iostream>

void EntityJumpModule::update(float dt, bool onGround)
{
    m_canJump = false;
    // if (m_jumpHoldTimer >= m_jumpHoldDuration)
    // {
    //     m_canJump = false;
    // }

    // if (m_canJump)
    // {
    //     m_jumpHoldTimer += dt;
    // }

    // if (onGround)
    // {
    //     m_jumpHoldTimer = 0.0f;
    // }

    if (!onGround)
    {
        m_jumpCoyoteTimerEnable = true;
    }

    if (m_jumpRequested && !onGround)
    {
        m_jumpBufferTimerEnable = true;
        m_jumpBufferTimer = 0.0f;
    }

    if (onGround && m_jumpRequested)
    {
        m_canJump = true;
    }

    if (m_jumpBufferTimerEnable)
    {
        if (onGround && m_jumpBufferTimer < m_jumpBufferDuration)
        {
            m_canJump = true;
            m_jumpBufferTimerEnable = false;
            m_jumpBufferTimer = 0.0f;
        }
        else
        {
            m_jumpBufferTimer += dt;
        }
    }

    // if (m_jumpCoyoteTimerEnable)
    // {
    //     if (!onGround && m_jumpCoyoteTimer < m_jumpCoyoteDuration &&
    //         m_jumpRequested)
    //     {
    //         m_canJump = true;
    //         m_jumpCoyoteTimerEnable = false;
    //         m_jumpCoyoteTimer = 0.0f;
    //     }
    //     else
    //     {
    //         m_jumpCoyoteTimer += dt;
    //     }
    // }

    if (onGround)
    {
        m_jumpBufferTimerEnable = false;
        m_jumpBufferTimer = 0.0f;
        m_jumpCoyoteTimerEnable = false;
        m_jumpCoyoteTimer = 0.0f;
    }

    m_jumpRequested = false;
}
