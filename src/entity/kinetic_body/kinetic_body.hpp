#pragma once

#include "math/vec.hpp"

class KineticBody
{
  public:
    KineticBody() = default;
    virtual ~KineticBody() = default;

    void applyGravity() { addForce({0.0f, m_gravity}); }
    void setGravity(float gravity) { m_gravity = gravity; }

    void update(float dt);

    void setPosition(Vec2i pos) { m_position = pos.toFloat(); }
    void setPositionFloat(Vec2f pos) { m_position = pos; }
    Vec2i getPosition() const { return m_position.toGrid(); }
    Vec2f getPositionFloat() const { return m_position; }
    Vec2i getLastPosition() const { return m_lastPosition.toGrid(); }
    Vec2f getLastPositionFloat() const { return m_lastPosition; }

    void setVelocityX(float x) { m_velocity.x = x; }
    void setVelocityY(float y) { m_velocity.y = y; }
    void setVelocity(Vec2f vel) { m_velocity = vel; }

    Vec2f getVelocity() const { return m_velocity; }

    void addForce(Vec2f force) { m_force += force; }

    void haltMotionInDirection(int dirX, int dirY);

    void move(float x, float y)
    {
        if (!m_movementRequested)
        {
            m_force += Vec2f(x, y);
        }

        m_movementRequested = true;
    }

  protected:
    bool m_movementRequested = false;

    Vec2f m_position;
    Vec2f m_lastPosition;
    Vec2f m_velocity;
    Vec2f m_force;
    Vec2f m_maxVelocity = {10, 10};
    float m_mass = 1.0f;
    float m_gravity = 0.0f;
};
