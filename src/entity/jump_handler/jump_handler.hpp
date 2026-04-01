#pragma once

#include "backend/timer/timer.hpp"

class JumpHandler
{
  public:
    JumpHandler()
    {
        m_coyoteTimer.setDurationInSeconds(0.15f);
    }
    virtual ~JumpHandler() = default;

    void requestJump() { m_jumpRequested = true; }

    void setJumpPower(float power) { m_jumpPower = power; }
    float getJumpVelocity() const { return -m_jumpPower; }
    void update(float dt, bool onGround);

    bool canJump() const { return m_canJump; }

  private:
    float m_jumpPower = 8.0f;
    bool m_canJump = false;
    bool m_jumpRequested = false;

    Timer m_coyoteTimer;
    bool m_canCoyoteJump = false;
};
