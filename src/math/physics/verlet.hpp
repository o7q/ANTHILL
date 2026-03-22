#pragma once

#include "math/vec.hpp"

class VerletBody
{
  public:
    VerletBody() = default;

    void integrate(float dt);

    void setPosition(float x, float y)
    {
        m_position = Vec2f(x, y);
        m_positionPrev = Vec2f(x, y);
    }
    Vec2f getPosition() const { return m_position; }
    Vec2f getPreviousPosition() const { return m_positionPrev; }

    void setVelocity(float x, float y, float dt)
    {
        m_positionPrev = m_position - Vec2f(x, y) * dt;
    }
    void addVelocity(float x, float y, float dt)
    {
        Vec2f currentVelocity = getVelocity(dt);
        setVelocity(currentVelocity.x + x, currentVelocity.y + y, dt);
    }
    Vec2f getVelocity(float dt) const
    {
        return (m_position - m_positionPrev) / dt;
    }

    void setForce(float x, float y) { m_force = Vec2f(x, y); }
    void addForce(float x, float y) { m_force += Vec2f(x, y); }
    void clearForces() { m_force = Vec2f(0.0f, 0.0f); }

    void setDamping(float x, float y) { m_damping = Vec2f(x, y); }
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
