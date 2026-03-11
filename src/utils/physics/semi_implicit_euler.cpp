
#include "semi_implicit_euler.hpp"

void SemiImplicitEulerBody::integrate(float dt)
{
    Vec2<float> acceleration = m_force / m_mass;

    m_velocity += acceleration * dt;
    Vec2<float> damping = Vec2<float>(std::pow(1.0f - m_damping.x, dt),
                                      std::pow(1.0f - m_damping.y, dt));
    m_velocity *= damping;
    m_position += m_velocity * dt;

    m_force = Vec2<float>(0.0f, 0.0f);
};
