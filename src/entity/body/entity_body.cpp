#include "entity_body.hpp"

#include "core/math/numbers.hpp"

void EntityBody::update(float dt)
{
    m_lastPosition = m_position;

    Vec2f targetDamping = {std::pow(m_targetDamping.x, dt), std::pow(m_targetDamping.y, dt)};

    m_velocity = m_velocityTarget + (m_velocity - m_velocityTarget) * targetDamping;
    m_position += m_velocity * dt;
    m_velocityTarget = {0.0f, 0.0f};
}

void EntityBody::haltMotionInDirection(Vec2i dir)
{
    if (Math::Numbers::sign(m_velocity.x) == Math::Numbers::sign(dir.x))
    {
        m_velocity.x = 0.0f;
    }
    if (Math::Numbers::sign(m_velocity.y) == Math::Numbers::sign(dir.y))
    {
        m_velocity.y = 0.0f;
    }

    if (Math::Numbers::sign(m_velocityTarget.x) == Math::Numbers::sign(dir.x))
    {
        m_velocityTarget.x = 0.0f;
    }
    if (Math::Numbers::sign(m_velocityTarget.y) == Math::Numbers::sign(dir.y))
    {
        m_velocityTarget.y = 0.0f;
    }
}
