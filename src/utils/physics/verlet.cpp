#include "verlet.hpp"

#include "backend/utils/vec.hpp"
#include <cmath>

void VerletBody::integrate(float dt)
{
    Vec2<float> velocity = m_position - m_positionPrev;
    Vec2<float> damping = Vec2<float>(std::pow(1.0f - m_damping.x, dt),
                                      std::pow(1.0f - m_damping.y, dt));
    velocity *= damping;

    Vec2<float> acceleration = m_force / m_mass;

    m_positionPrev = m_position;
    m_position += velocity + acceleration * dt * dt;

    m_force = Vec2<float>(0.0f, 0.0f);
}
