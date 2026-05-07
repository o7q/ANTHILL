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
    void cancelJump() { m_holdJumpTimer.stop(); }

    float getJumpPower() const { return m_jumpPower; }
    bool canApplyJumpPower() const { return m_holdJumpTimer.active(); }

  private:
    float m_jumpPower    = 4.5f;
    bool m_jumpRequested = false;

    Timer m_holdJumpTimer;
    Timer m_jumpBufferTimer;

    Timer m_coyoteTimer;
    bool m_allowCoyoteJump = false;

    int m_doubleJumpAmount  = 0;
    int m_doubleJumpCounter = 0;
};
