#pragma once

#include "math/physics/body.hpp"
#include "math/vec.hpp"

class SemiImplicitEulerBody : public PhysicsBody
{
  public:
    SemiImplicitEulerBody() = default;

    void setPosition(float x, float y) { m_position = Vec2<float>(x, y); }
    Vec2<float> getPosition() const { return m_position; }

    void integrate(float dt) override;

    void setVelocity(float x, float y) { m_velocity = Vec2<float>(x, y); }
    void setVelocityX(float x) { m_velocity.x = x; }
    void setVelocityY(float y) { m_velocity.y = y; }
    Vec2<float> getVelocity() const { return m_velocity; }
    Vec2<float> getForce() const { return m_force; }

    void setForce(float x, float y) { m_force = Vec2<float>(x, y); }
    void addForce(float x, float y) { m_force += Vec2<float>(x, y); }
    void clearForces() { m_force = Vec2<float>(0.0f, 0.0f); }

    void setDamping(float x, float y) { m_damping = Vec2<float>(x, y); }
    Vec2<float> getDamping() const { return m_damping; }

  protected:
    Vec2<float> m_velocity = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_force = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_damping = Vec2<float>(0.0f, 0.0f);
    float m_mass = 1.0f;
};
