#include "bullet.hpp"

#include <cmath>

Bullet::Bullet(float start_x, float start_y, float target_x, float target_y)
{
    float x = target_x - start_x;
    float y = target_y - start_y;

    float m = std::sqrt(x * x + y * y);

    m_dx = x / m;
    m_dy = y / m;

    m_position.x = start_x;
    m_position.y = start_y;
}

void Bullet::update(float dt)
{
    if (hit())
    {
        return;
    }

    m_position.x += m_dx * m_speed * dt;
    m_position.y += m_dy * m_speed * dt;
}

bool Bullet::hit() const
{
    return m_hit_object != nullptr;
}