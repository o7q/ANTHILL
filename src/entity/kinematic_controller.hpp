#pragma once

#include "types/physics/semi_implicit_euler.hpp"

class KinematicController
{
  public:
    KinematicController() {}

    void jump()
    {
        if (!m_canJump)
        {
            return;
        }

        Vec2<float> currentVelocity = m_body.getVelocity();
        m_body.setVelocity(currentVelocity.x, -m_jump_power);
    }
    void update(float dt)
    {
        // m_body.addForce(0, m_gravity);
        if (!m_inputRecieved)
        {
            m_body.setDamping(1, 1);
        }
        else
        {
            m_body.setDamping(0, 0);
        }
        m_body.integrate(dt);
        m_inputRecieved = false;
    }

    void setPosition(float x, float y) { m_body.setPosition(x, y); }
    Vec2<float> getPosition() const { return m_body.getPosition(); }

    void move(float x, float y)
    {
        if (x != 0)
        {
            m_body.setVelocityX(x);
        }
        if (y != 0)
        {
            m_body.setVelocityY(y);
        }

        m_inputRecieved = true;
    }
    void setVelocity(float x, float y) { m_body.setVelocity(x, y); }
    Vec2<float> getVelocity() const { return m_body.getVelocity(); }
    void enableJump(bool v) { m_canJump = v; }

  private:
    float m_jump_power = 7.0f;
    float m_gravity = 0.4f;
    bool m_inputRecieved = false;
    SemiImplicitEulerBody m_body;

    bool m_canJump = true;
};
