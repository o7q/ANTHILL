#pragma once

#include "math/physics/semi_implicit_euler.hpp"
#include "math/vec.hpp"

class KineticBody
{
  public:
    KineticBody() = default;
    virtual ~KineticBody() = default;

    void applyGravity() { m_body.addForce(0.0f, m_gravity); }
    void setGravity(float gravity) { m_gravity = gravity; }

    void update(float dt);

    void setPosition(int x, int y)
    {
        return m_body.setPosition(static_cast<float>(x), static_cast<float>(y));
    }
    void setPositionFloat(float x, float y) { m_body.setPosition(x, y); }
    Vec2<int> getPosition() const { return m_body.getPosition().toGrid(); }
    Vec2<float> getPositionFloat() const { return m_body.getPosition(); }
    Vec2<int> getLastPosition() const { return m_lastPos.toGrid(); }
    Vec2<float> getLastPositionFloat() const { return m_lastPos; }

    void setVelocityX(float x) { m_body.setVelocityX(x); }
    void setVelocityY(float y) { m_body.setVelocityY(y); }
    void setVelocity(float x, float y) { m_body.setVelocity(x, y); }

    Vec2<float> getVelocity() const { return m_body.getVelocity(); }

    void addForce(float x, float y) { m_body.addForce(x, y); }

    void haltMotionInDirection(int dirX, int dirY);

  protected:
    SemiImplicitEulerBody m_body;

    float m_gravity = 0.0f;
    Vec2<float> m_lastPos = {0, 0};

    Vec2<float> m_maxVelocity = {10, 10};
};
