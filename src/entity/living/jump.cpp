#include "living_entity.hpp"

void LivingEntity::updateJumpPhysics(float dt)
{
    bool onGround = m_interactionBox.getWorldHandler().againstSolidSurface(
        m_body.getPosition(), BoundingBox::Side::Bottom);

    if (onGround)
    {
        m_jumped = false;
    }

    if (!onGround)
    {
        m_jumpCoyoteTimerEnable = true;
    }

    if (m_jumpRequested && !onGround)
    {
        m_jumpBufferTimerEnable = true;
        m_jumpBufferTimer = 0.0f;
    }

    if (onGround && m_jumpRequested && !m_jumped)
    {
        m_body.setVelocityY(-m_jumpHeight);
        m_jumped = true;
    }

    if (m_jumpBufferTimerEnable)
    {
        if (onGround && m_jumpBufferTimer < m_jumpBufferDuration && !m_jumped)
        {
            m_body.setVelocityY(-m_jumpHeight);
            m_jumped = true;
            m_jumpBufferTimerEnable = false;
            m_jumpBufferTimer = 0.0f;
        }
        else
        {
            m_jumpBufferTimer += dt;
        }
    }

    if (m_jumpCoyoteTimerEnable)
    {
        if (!onGround && m_jumpCoyoteTimer < m_jumpCoyoteDuration &&
            m_jumpRequested && !m_jumped)
        {
            m_body.setVelocityY(-m_jumpHeight);
            m_jumped = true;
            m_jumpCoyoteTimerEnable = false;
            m_jumpCoyoteTimer = 0.0f;
        }
        else
        {
            m_jumpCoyoteTimer += dt;
        }
    }

    if (onGround)
    {
        m_jumpBufferTimerEnable = false;
        m_jumpBufferTimer = 0.0f;
        m_jumpCoyoteTimerEnable = false;
        m_jumpCoyoteTimer = 0.0f;
    }

    m_jumpRequested = false;
}