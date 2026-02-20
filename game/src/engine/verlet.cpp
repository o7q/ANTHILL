#include "verlet.hpp"

#include "vec.hpp"

void VerletBody::update(float dt)
{
    Vec2<float> velocity = m_position - m_positionPrev;
    Vec2<float> acceleration = m_force / m_mass;

    Vec2<float> damp = Vec2<float>(1.0f, 1.0f);
    if (p_world_properties)
    {
        damp.x = 1.0f / (p_world_properties->air_resistance.x + 1.0f);
        damp.y = 1.0f / (p_world_properties->air_resistance.y + 1.0f);
    }

    m_positionPrev = m_position;
    m_position += velocity * damp + acceleration * dt * dt;
}
