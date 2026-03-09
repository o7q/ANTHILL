#pragma once

#include "entity/base/entity.hpp"
#include "world/particle/particle_handler.hpp"

class LivingEntity : public Entity
{
  public:
    LivingEntity(ParticleHandler &particles) : Entity(particles) {}
    virtual ~LivingEntity() = default;

  protected:
    void jump() { m_jumpRequested = true; }

    void updateInternal(float dt) override
    {
        updateJumpPhysics(dt);
        updateMotion(dt);
    }

    void setJumpHeight(float jumpHeight) { m_jumpHeight = jumpHeight; }

  private:
    void updateJumpPhysics(float dt);

  private:
    float m_jumpHeight = 7.0f;

    bool m_jumpRequested = false;
    bool m_jumped = false;
    const float m_jumpCoyoteDuration = 8.0f;
    bool m_jumpBufferTimerEnable = false;
    float m_jumpBufferTimer = 0.0f;
    const float m_jumpBufferDuration = 7.0f;
    bool m_jumpCoyoteTimerEnable = false;
    float m_jumpCoyoteTimer = 0.0f;
};
