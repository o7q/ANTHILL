#pragma once

class JumpModule
{
  public:
    JumpModule() = default;
    virtual ~JumpModule() = default;

    void requestJump() { m_jumpRequested = true; }

    void setJumpHeight(float jumpHeight) { m_jumpHeight = jumpHeight; }
    float getJumpHeight() const { return m_jumpHeight; }
    void update(float dt, bool onGround);

    bool canJump() const { return m_canJump; }

  private:
    float m_jumpHeight = 7.0f;

    bool m_jumpRequested = false;
    bool m_canJump = false;
    const float m_jumpCoyoteDuration = 8.0f;
    bool m_jumpBufferTimerEnable = false;
    float m_jumpBufferTimer = 0.0f;
    const float m_jumpBufferDuration = 7.0f;
    bool m_jumpCoyoteTimerEnable = false;
    float m_jumpCoyoteTimer = 0.0f;
};
