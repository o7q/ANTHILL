#pragma once

#include "backend/types/vec.hpp"

class SemiImplicitEulerBody
{
  public:
    SemiImplicitEulerBody() = default;

    void setPosition(float x, float y) { m_position = Vec2<float>(x, y); }
    Vec2<float> getPosition() const { return m_position; }

    void integrate(float dt)
    {
        Vec2<float> acceleration = m_force / m_mass;

        Vec2<float> damping_coefficient =
            Vec2<float>(1.0f - m_damp.x, 1.0f - m_damp.y);

        m_velocity += acceleration * dt;
        m_velocity *= Vec2<float>(std::pow(damping_coefficient.x, dt),
                                  std::pow(damping_coefficient.y, dt));
        m_position += m_velocity * dt;

        m_force = Vec2<float>(0.0f, 0.0f);
    }

    void setVelocity(float x, float y) { m_velocity = Vec2<float>(x, y); }
    void setVelocityX(float x) { m_velocity.x = x; }
    void setVelocityY(float y) { m_velocity.y = y; }
    Vec2<float> getVelocity() const { return m_velocity; }

    void setForce(float x, float y) { m_force = Vec2<float>(x, y); }
    void addForce(float x, float y) { m_force += Vec2<float>(x, y); }
    void clearForces() { m_force = Vec2<float>(0.0f, 0.0f); }

    void setDamping(float x, float y) { m_damp = Vec2<float>(x, y); }
    Vec2<float> getDamping() const { return m_damp; }

  protected:
    Vec2<float> m_position = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_velocity = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_force = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_damp = Vec2<float>(0.0f, 0.0f);
    float m_mass = 1.0f;
};
