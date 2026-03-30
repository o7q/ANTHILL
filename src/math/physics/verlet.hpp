#pragma once

#include "math/vec.hpp"

class VerletBody
{
  public:
    VerletBody() = default;

    void integrate(float dt);

    void setPosition(Vec2f pos)
    {
        m_position = pos;
        m_positionPrev = pos;
    }
    Vec2f getPosition() const { return m_position; }
    Vec2f getPreviousPosition() const { return m_positionPrev; }

    void setVelocity(Vec2f vel, float dt)
    {
        m_positionPrev = m_position - vel * dt;
    }
    void addVelocity(Vec2f vel, float dt)
    {
        setVelocity(getVelocity(dt) + vel, dt);
    }
    Vec2f getVelocity(float dt) const
    {
        return (m_position - m_positionPrev) / dt;
    }

    void setForce(Vec2f force) { m_force = force; }
    void addForce(Vec2f force) { m_force += force; }
    void clearForces() { m_force = Vec2f(0.0f, 0.0f); }

    void setDamping(Vec2f damping) { m_damping = damping; }
    Vec2f getDamping() const { return m_damping; }

    void setMass(float mass) { m_mass = mass; }
    float getMass() const { return m_mass; }

  private:
    Vec2f m_position = {0.0f, 0.0f};
    Vec2f m_positionPrev = {0.0f, 0.0f};
    Vec2f m_force = {0.0f, 0.0f};
    Vec2f m_damping = {0.0f, 0.0f};
    float m_mass = 1.0f;
};
