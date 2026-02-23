#pragma once

#include "engine/vec.hpp"

class VerletBody
{
  public:
    VerletBody() = default;

    void update(float dt);

    void setPosition(float x, float y)
    {
        m_position = Vec2<float>(x, y);
        m_positionPrev = Vec2<float>(x, y);
    }

    void setVelocity(float x, float y, float dt)
    {
        m_positionPrev = m_position - Vec2<float>(x, y) * dt;
    }

    void setForce(float x, float y) { m_force = Vec2<float>(x, y); }
    void addForce(float x, float y) { m_force += Vec2<float>(x, y); }
    void clearForces() { m_force = Vec2<float>(0.0f, 0.0f); }

    void setMass(float mass) { m_mass = mass; }
    void setRestitution(float restitution) { m_restitution = restitution; }
    float getRestitution() const { return m_restitution; }

    Vec2<float> getPosition() const { return m_position; }
    Vec2<float> getPreviousPosition() const { return m_positionPrev; }
    Vec2<float> getVelocity(float dt) const
    {
        return (m_position - m_positionPrev) / dt;
    }

  private:
    float m_mass = 1.0f;
    float m_restitution = 1.0f;
    Vec2<float> m_position = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_positionPrev = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_force = Vec2<float>(0.0f, 0.0f);
};
