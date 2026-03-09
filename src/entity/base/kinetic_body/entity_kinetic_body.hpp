#pragma once

#include "backend/types/vec.hpp"
#include "types/physics/semi_implicit_euler.hpp"
#include "utils/math/numbers.hpp"

class EntityKineticBody
{
  public:
    EntityKineticBody() = default;
    virtual ~EntityKineticBody() = default;

    void applyGravity() { m_body.addForce(0.0f, m_gravity); }
    void setGravity(float gravity) { m_gravity = gravity; }

    void update(float dt)
    {
        m_lastPos = getPosition();

        if (std::abs(m_body.getVelocity().x) < 0.01f)
        {
            m_body.setVelocityX(0);
        }
        if (std::abs(m_body.getVelocity().y) < 0.01f)
        {
            m_body.setVelocityY(0);
        }

        m_body.integrate(dt);
    }

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

    void haltMotionInDirection(int dirX, int dirY)
    {
        Vec2<float> force = m_body.getForce();
        if (Utils::Math::Numbers::sign(force.x) ==
            Utils::Math::Numbers::sign(dirX))
        {
            force.x = 0.0f;
        }
        if (Utils::Math::Numbers::sign(force.y) ==
            Utils::Math::Numbers::sign(dirY))
        {
            force.y = 0.0f;
        }
        m_body.setForce(force.x, force.y);

        Vec2<float> vel = m_body.getVelocity();
        if (Utils::Math::Numbers::sign(vel.x) ==
            Utils::Math::Numbers::sign(dirX))
        {
            vel.x = 0.0f;
        }
        if (Utils::Math::Numbers::sign(vel.y) ==
            Utils::Math::Numbers::sign(dirY))
        {
            vel.y = 0.0f;
        }
        m_body.setVelocity(vel.x, vel.y);
    }

  protected:
    SemiImplicitEulerBody m_body;

    float m_gravity = 0.0f;
    Vec2<float> m_movementDamping = Vec2<float>(0.0f, 0.0f);
    Vec2<int> m_lastPos = {0, 0};
};
