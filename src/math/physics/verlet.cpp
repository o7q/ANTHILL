#include "verlet.hpp"

void VerletBody::integrate(float dt)
{
    Vec2f velocity = m_position - m_positionPrev;

    m_positionPrev = m_position;
    m_position += velocity + m_force * dt * dt;

    m_force = Vec2f(0.0f, 0.0f);
}
