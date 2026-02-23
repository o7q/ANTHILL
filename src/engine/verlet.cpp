#include "verlet.hpp"

#include "engine/vec.hpp"

void VerletBody::update(float dt)
{
    Vec2<float> velocity = m_position - m_positionPrev;

    Vec2<float> acceleration = m_force / m_mass;

    m_positionPrev = m_position;
    m_position += velocity + acceleration * dt * dt;

    m_force = Vec2<float>(0.0f, 0.0f);
}
