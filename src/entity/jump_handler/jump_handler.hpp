#pragma once

#include "backend/timer/timer.hpp"

class JumpHandler
{
  public:
    JumpHandler()
    {
        m_coyoteTimer.setDurationInSeconds(0.1f);
        m_holdJumpTimer.setDurationInSeconds(0.2f);
        m_jumpBufferTimer.setDurationInSeconds(0.1f);
    }
    virtual ~JumpHandler() = default;

    void update(float dt, bool onGround);

    void requestJump() { m_jumpRequested = true; }
    bool canJump() const { return m_holdJumpTimer.active(); }
    void cancelJump() { m_holdJumpTimer.stop(); }

    void setJumpPower(float power) { m_jumpPower = power; }
    void setJumpHoldTime(float time)
    {
        m_holdJumpTimer.setDurationInSeconds(time);
    }
    void setCoyoteTime(float time) { m_coyoteTimer.setDurationInSeconds(time); }
    void setDoubleJumpAmount(int amount) { m_doubleJumpAmount = amount; }

    float getJumpPower() const { return m_jumpPower; }

  private:
    float m_jumpPower = 4.5f;
    bool m_jumpRequested = false;

    Timer m_holdJumpTimer;
    Timer m_jumpBufferTimer;

    Timer m_coyoteTimer;
    bool m_allowCoyoteJump = false;

    int m_doubleJumpAmount = 0;
    int m_doubleJumpCounter = 0;
};
