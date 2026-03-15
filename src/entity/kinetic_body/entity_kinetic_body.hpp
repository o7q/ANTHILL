#pragma once

#include "backend/utils/vec.hpp"
#include "utils/physics/semi_implicit_euler.hpp"

class EntityKineticBody
{
  public:
    EntityKineticBody() = default;
    virtual ~EntityKineticBody() = default;

    void applyGravity() { m_body.addForce(0.0f, m_gravity); }
    void setGravity(float gravity) { m_gravity = gravity; }

    void update(float dt);

    void setPosition(int x, int y)
    {
        m_body.setPosition(static_cast<float>(x), static_cast<float>(y));
    }
    Vec2<int> getPosition() const { return m_body.getPosition().toGrid(); }
    Vec2<int> getLastPosition() const { return m_lastPos; }

    void setMovementDamping(float x, float y)
    {
        m_movementDamping = Vec2<float>(x, y);
    }

    void setVelocityX(float x) { m_body.setVelocityX(x); }
    void setVelocityY(float y) { m_body.setVelocityY(y); }

    Vec2<float> getVelocity() const { return m_body.getVelocity(); }

    void addForce(float x, float y) { m_body.addForce(x, y); }

    void haltMotionInDirection(int dirX, int dirY);

  protected:
    SemiImplicitEulerBody m_body;

    float m_gravity = 0.0f;
    Vec2<float> m_movementDamping = Vec2<float>(0.0f, 0.0f);
    Vec2<int> m_lastPos = {0, 0};
};
