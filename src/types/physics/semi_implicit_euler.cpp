
#include "types/physics/semi_implicit_euler.hpp"

void SemiImplicitEulerBody::integrate(float dt)
{
    Vec2<float> acceleration = m_force / m_mass;

    Vec2<float> damping_coefficient =
        Vec2<float>(1.0f - m_damp.x, 1.0f - m_damp.y);

    m_velocity += acceleration * dt;
    m_velocity *= Vec2<float>(std::pow(damping_coefficient.x, dt),
                              std::pow(damping_coefficient.y, dt));
    m_position += m_velocity * dt;

    m_force = Vec2<float>(0.0f, 0.0f);
};
