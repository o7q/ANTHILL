#pragma once

#include "backend/types/vec.hpp"

class PhysicsBody
{
  public:
    PhysicsBody() = default;

    virtual void update(float dt) = 0;

    void setPosition(float x, float y) { m_position = Vec2<float>(x, y); }
    Vec2<float> getPosition() const { return m_position; }

    void setMass(float mass) { m_mass = mass; }
    float getMass() const { return m_mass; }

  protected:
    Vec2<float> m_position = Vec2<float>(0.0f, 0.0f);
    float m_mass = 1.0f;
};
