#pragma once

class JumpHandler
{
  public:
    JumpHandler() = default;
    virtual ~JumpHandler() = default;

    void requestJump() { m_jumpRequested = true; }
    void cancelJump() { m_canJump = false; }

    void setJumpPower(float power) { m_jumpPower = power; }
    float getJumpPower() const { return m_jumpPower; }
    void update(float dt, bool onGround);

    bool canJump() const { return m_canJump; }

    void setCoyoteDuration(float duration) { m_jumpCoyoteDuration = duration; }
    void setBufferDuration(float duration) { m_jumpBufferDuration = duration; }
    void setHoldDuration(float duration) { m_jumpHoldDuration = duration; }

  private:
    float m_jumpPower = 8.0f;

    bool m_jumpRequested = false;
    bool m_canJump = false;
    float m_jumpCoyoteDuration = 8.0f;
    bool m_jumpBufferTimerEnable = false;
    float m_jumpBufferTimer = 0.0f;
    float m_jumpBufferDuration = 7.0f;
    bool m_jumpCoyoteTimerEnable = false;
    float m_jumpCoyoteTimer = 0.0f;

    float m_jumpHoldTimer = 0.0f;
    float m_jumpHoldDuration = 20.0f;
};
