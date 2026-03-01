#pragma once

#include "backend/types/vec.hpp"
#include "types/physics/body.hpp"

class VerletBody : public PhysicsBody
{
  public:
    VerletBody() = default;

    void update(float dt) override;

    void stopInPosition(float x, float y)
    {
        m_position = Vec2<float>(x, y);
        m_positionPrev = Vec2<float>(x, y);
    }

    void setVelocity(float x, float y, float dt)
    {
        m_positionPrev = m_position - Vec2<float>(x, y) * dt;
    }

    void addVelocity(float x, float y, float dt)
    {
        Vec2<float> currentVelocity = getVelocity(dt);
        setVelocity(currentVelocity.x + x, currentVelocity.y + y, dt);
    }

    void setForce(float x, float y) { m_force = Vec2<float>(x, y); }
    void addForce(float x, float y) { m_force += Vec2<float>(x, y); }
    void clearForces() { m_force = Vec2<float>(0.0f, 0.0f); }

    Vec2<float> getPreviousPosition() const { return m_positionPrev; }
    Vec2<float> getVelocity(float dt) const
    {
        return (m_position - m_positionPrev) / dt;
    }

    void setDrag(float x, float y) { m_drag = Vec2<float>(x, y); }

  private:
    Vec2<float> m_positionPrev = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_force = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_drag = Vec2<float>(0.0f, 0.0f);
};
