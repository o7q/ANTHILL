#pragma once

#include "core/math/geometry/vec.hpp"

class EntityBody
{
  public:
    EntityBody()          = default;
    virtual ~EntityBody() = default;

    void update(float dt);

    void applyGravity() { m_velocityTarget.y = m_gravity; }
    void setGravity(float gravity) { m_gravity = gravity; }

    void setVelocity(Vec2f vel)
    {
        m_velocity       = vel;
        m_velocityTarget = vel;
    }
    void setVelocityX(float x)
    {
        m_velocity.x       = x;
        m_velocityTarget.x = x;
    }
    void setVelocityY(float y)
    {
        m_velocity.y       = y;
        m_velocityTarget.y = y;
    }
    void setVelocityTarget(Vec2f target) { m_velocityTarget = target; }
    void setVelocityTargetX(float x) { m_velocityTarget.x = x; }
    void setVelocityTargetY(float y) { m_velocityTarget.y = y; }
    void addVelocityTarget(Vec2f vel) { m_velocityTarget += vel; }
    void setTargetDamping(Vec2f damping) { m_targetDamping = damping; }
    Vec2f getVelocity() const { return m_velocity; }
    Vec2f getVelocityTarget() const { return m_velocityTarget; }

    void setPosition(Vec2i pos) { m_position = pos.toFloat(); }
    void setPositionFloat(Vec2f pos) { m_position = pos; }
    Vec2i getPosition() const { return m_position.toGrid(); }
    Vec2f getPositionFloat() const { return m_position; }
    Vec2i getLastPosition() const { return m_lastPosition.toGrid(); }
    Vec2f getLastPositionFloat() const { return m_lastPosition; }

    void haltMotionInDirection(Vec2i dir);

  protected:
    Vec2f m_position;
    Vec2f m_lastPosition;

    Vec2f m_velocity;
    Vec2f m_velocityTarget;
    Vec2f m_targetDamping = {0.5f, 0.97f};

    float m_gravity = 12.0f;
};
