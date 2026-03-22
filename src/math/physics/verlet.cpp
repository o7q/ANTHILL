#include "verlet.hpp"

#include <cmath>

void VerletBody::integrate(float dt)
{
    Vec2f velocity = m_position - m_positionPrev;
    Vec2f damping = Vec2f(std::pow(1.0f - m_damping.x, dt),
                          std::pow(1.0f - m_damping.y, dt));
    velocity *= damping;

    Vec2f acceleration = m_force / m_mass;

    m_positionPrev = m_position;
    m_position += velocity + acceleration * dt * dt;

    m_force = Vec2f(0.0f, 0.0f);
}
