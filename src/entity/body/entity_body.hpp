#pragma once

#include "px/basic_types/vec.hpp"

class EntityBody
{
  public:
    EntityBody()          = default;
    virtual ~EntityBody() = default;

    void update(float dt);

    void applyGravity() { m_velocityTarget.y += m_gravity; }
    void setGravity(float gravity) { m_gravity = gravity; }

    void setVelocity(px::Vec2f vel)
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
    void setVelocityTarget(px::Vec2f target) { m_velocityTarget = target; }
    void setVelocityTargetX(float x) { m_velocityTarget.x = x; }
    void setVelocityTargetY(float y) { m_velocityTarget.y = y; }
    void addVelocityTarget(px::Vec2f vel) { m_velocityTarget += vel; }
    void setTargetDamping(px::Vec2f damping) { m_targetDamping = damping; }
    void setTargetDampingX(float x) { m_targetDamping.x = x; }
    void setTargetDampingY(float y) { m_targetDamping.y = y; }
    px::Vec2f getVelocity() const { return m_velocity; }
    px::Vec2f getVelocityTarget() const { return m_velocityTarget; }

    void setPosition(px::Vec2i pos) { m_position = pos.toFloat(); }
    void setPositionFloat(px::Vec2f pos) { m_position = pos; }
    px::Vec2i getPosition() const { return m_position.toGrid(); }
    px::Vec2f getPositionFloat() const { return m_position; }
    px::Vec2i getLastPosition() const { return m_lastPosition.toGrid(); }
    px::Vec2f getLastPositionFloat() const { return m_lastPosition; }

    void haltMotionInDirection(px::Vec2i dir);

  protected:
    px::Vec2f m_position;
    px::Vec2f m_lastPosition;

    px::Vec2f m_velocity;
    px::Vec2f m_velocityTarget;
    px::Vec2f m_targetDamping = {0.5f, 0.95f};

    float m_gravity = 8.0f;
};
