#pragma once

#include "math/physics/body.hpp"
#include "math/vec.hpp"

class VerletBody : public PhysicsBody
{
  public:
    VerletBody() = default;

    void integrate(float dt) override;

    void setPosition(float x, float y)
    {
        m_position = Vec2<float>(x, y);
        m_positionPrev = Vec2<float>(x, y);
    }
    Vec2<float> getPosition() const { return m_position; }
    Vec2<float> getPreviousPosition() const { return m_positionPrev; }

    void setVelocity(float x, float y, float dt)
    {
        m_positionPrev = m_position - Vec2<float>(x, y) * dt;
    }
    void addVelocity(float x, float y, float dt)
    {
        Vec2<float> currentVelocity = getVelocity(dt);
        setVelocity(currentVelocity.x + x, currentVelocity.y + y, dt);
    }
    Vec2<float> getVelocity(float dt) const
    {
        return (m_position - m_positionPrev) / dt;
    }

    void setForce(float x, float y) { m_force = Vec2<float>(x, y); }
    void addForce(float x, float y) { m_force += Vec2<float>(x, y); }
    void clearForces() { m_force = Vec2<float>(0.0f, 0.0f); }

    void setDamping(float x, float y) { m_damping = Vec2<float>(x, y); }
    Vec2<float> getDamping() const { return m_damping; }

    void setMass(float mass) { m_mass = mass; }
    float getMass() const { return m_mass; }

  private:
    Vec2<float> m_positionPrev = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_force = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_damping = Vec2<float>(0.0f, 0.0f);
    float m_mass = 1.0f;
};
