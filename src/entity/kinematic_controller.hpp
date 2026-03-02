#pragma once

#include "entity/kinematic_body.hpp"

class KinematicController
{
  public:
    KinematicController() {}

    void jump()
    {
        m_body.setVelocityY(-m_jump_power * (1.0f - m_movementDamping.y));
    }

    void applyGravity() { m_body.addForce(0, m_gravity); }

    void update(float dt)
    {
        if (!m_inputRecieved)
        {
            m_body.setDamping(1, 0);
        }
        else
        {
            m_body.setDamping(0, 0);
        }

        m_body.integrate(dt);
        m_inputRecieved = false;
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

    void move(float x, float y)
    {
        if (x != 0)
        {
            m_body.setVelocityX(x * (1.0f - m_movementDamping.x));
        }
        if (y != 0)
        {
            m_body.setVelocityY(y * (1.0f - m_movementDamping.y));
        }

        m_inputRecieved = true;
    }
    void setVelocity(float x, float y) { m_body.setVelocity(x, y); }
    Vec2<float> getVelocity() const { return m_body.getVelocity(); }

    void setMovementDamping(float x, float y)
    {
        m_movementDamping = Vec2<float>(x, y);
    }

  private:
    KinematicBody m_body;

    float m_jump_power = 7.0f;
    float m_gravity = 0.4f;
    bool m_inputRecieved = false;
    Vec2<float> m_movementDamping = Vec2<float>(0.0f, 0.0f);
};
