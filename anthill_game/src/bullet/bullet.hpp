#pragma once

#include <cmath>

#include "../engine/math/vector.hpp"

class Bullet
{
public:
    Bullet(float start_x, float start_y, float target_x, float target_y)
    {
        float x = target_x - start_x;
        float y = target_y - start_y;

        float m = std::sqrt(x * x + y * y);

        m_dx = x / m;
        m_dy = y / m;

        m_position.x = start_x;
        m_position.y = start_y;
    }

    void setSpeed(float speed) { m_speed = speed; }

    void update(float dt)
    {
        m_position.x += m_dx * m_speed * dt;
        m_position.y += m_dy * m_speed * dt;
    }

    Vec2<float> getPosition() const { return m_position; }

private:
    Vec2<float> m_position;

    float m_dx = 0.0f;
    float m_dy = 0.0f;
    float m_speed = 1.0f;
};