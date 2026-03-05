#pragma once

#include "entity/kinematic_body.hpp"

class KinematicController
{
  public:
    KinematicController() {}

    void jump() { m_body.setVelocityY(-m_jump_power); }

    void applyGravity() { m_body.addForce(0, m_gravity); }

    void update(float dt)
    {
        m_body.setDamping(0.6, 0);
        m_body.integrate(dt);
    }

    void haltMotionInDirection(int dirX, int dirY)
    {
        m_body.haltMotionInDirection(dirX, dirY);
    }

    void setPosition(int x, int y)
    {
        m_body.setPosition(static_cast<float>(x), static_cast<float>(y));
    }
    Vec2<int> getPosition() const { return m_body.getPosition().toGrid(); }

    void setVelocity(float x, float y) { m_body.setVelocity(x, y); }
    void setVelocityX(float x) { m_body.setVelocityX(x); }
    void setVelocityY(float y) { m_body.setVelocityX(y); }
    void addForce(float x, float y) { m_body.addForce(x, y); }
    Vec2<float> getVelocity() const { return m_body.getVelocity(); }

    void setMovementDamping(float x, float y)
    {
        m_movementDamping = Vec2<float>(x, y);
    }

    bool horizontallyInMotion() { return m_body.horizontallyInMotion(); }
    bool verticallyInMotion() { return m_body.verticallyInMotion(); }

  private:
    KinematicBody m_body;

    float m_jump_power = 7.0f;
    float m_gravity = 0.4f;
    Vec2<float> m_movementDamping = Vec2<float>(0.0f, 0.0f);
};
