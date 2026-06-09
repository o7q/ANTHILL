#pragma once

#include "core/timer/timer.hpp"

class JumpHandler
{
  public:
    JumpHandler()
    {
        m_coyoteTimer.setDurationInSeconds(0.1f);
        m_holdTimer.setDurationInSeconds(0.2f);
        m_bufferTimer.setDurationInSeconds(0.1f);
    }
    virtual ~JumpHandler() = default;

    void update(float dt, bool onGround);

    void requestJump() { m_jumpRequested = true; }
    void cancelJump() { m_holdTimer.stop(); }

    bool jumped() const { return m_jumped; }

    float getJumpPower() const { return m_jumpPower; }
    bool canApplyJumpPower() const { return m_holdTimer.active(); }

    void setJumpPower(float jumpPower) { m_jumpPower = jumpPower; }
    void setCoyoteTime(float coyoteTime) { m_coyoteTimer.setDurationInSeconds(coyoteTime); }
    void setHoldLength(float holdLength) { m_holdTimer.setDurationInSeconds(holdLength); }
    void setBufferTime(float bufferTime) { m_bufferTimer.setDurationInSeconds(bufferTime); }

  private:
    bool m_jumped = false;

    float m_jumpPower    = 5.0f;
    bool m_jumpRequested = false;

    Timer m_holdTimer;
    Timer m_bufferTimer;

    Timer m_coyoteTimer;
    bool m_allowCoyoteJump = false;
};
