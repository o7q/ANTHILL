#pragma once

#include "math/vec.hpp"

class KineticBody
{
  public:
    KineticBody() = default;
    virtual ~KineticBody() = default;

    void applyGravity() { addForce(0.0f, m_gravity); }
    void setGravity(float gravity) { m_gravity = gravity; }

    void update(float dt)
    {
        Vec2f acceleration = m_force / m_mass;

        m_velocity += acceleration * dt;
        m_position += m_velocity * dt;

        m_force = Vec2f(0.0f, 0.0f);
    }

    void setPosition(int x, int y) { m_position = Vec2i(x, y).toFloat(); }
    void setPositionFloat(float x, float y) { m_position = Vec2f(x, y); }
    Vec2i getPosition() const { return m_position.toGrid(); }
    Vec2f getPositionFloat() const { return m_position; }
    Vec2i getLastPosition() const { return m_lastPosition.toGrid(); }
    Vec2f getLastPositionFloat() const { return m_lastPosition; }

    void setVelocityX(float x) { m_velocity.x = x; }
    void setVelocityY(float y) { m_velocity.y = y; }
    void setVelocity(float x, float y) { m_velocity = Vec2f(x, y); }

    Vec2f getVelocity() const { return m_velocity; }

    void addForce(float x, float y) { m_force += Vec2f(x, y); }

    void haltMotionInDirection(int dirX, int dirY);

  protected:
    Vec2f m_position;
    Vec2f m_lastPosition;
    Vec2f m_velocity;
    Vec2f m_force;
    Vec2f m_maxVelocity = {10, 10};
    float m_mass = 1.0f;
    float m_gravity = 0.0f;
};
