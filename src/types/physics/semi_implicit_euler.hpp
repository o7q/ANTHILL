#pragma once

#include "types/physics/body.hpp"
class SemiImplicitEulerBody : public PhysicsBody
{
  public:
    SemiImplicitEulerBody() = default;

    void update(float dt) override
    {
        Vec2<float> acceleration = m_force / m_mass;

        m_velocity += acceleration * dt;
        m_position += m_velocity * dt;

        m_force = Vec2<float>(0.0f, 0.0f);
    }

    void setVelocity(float x, float y) { m_velocity = Vec2<float>(x, y); }

    void setForce(float x, float y) { m_force = Vec2<float>(x, y); }
    void addForce(float x, float y) { m_force += Vec2<float>(x, y); }
    void clearForces() { m_force = Vec2<float>(0.0f, 0.0f); }

    Vec2<float> getVelocity(float dt) const { return m_velocity; }

  private:
    Vec2<float> m_velocity = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_force = Vec2<float>(0.0f, 0.0f);
};
