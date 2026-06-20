#include "entity_body.hpp"

#include "px/utils/numbers.hpp"

void EntityBody::update(float dt)
{
    m_lastPosition = m_position;

    px::Vec2f targetDamping = {std::pow(m_targetDamping.x, dt), std::pow(m_targetDamping.y, dt)};

    m_velocity = m_velocityTarget + (m_velocity - m_velocityTarget) * targetDamping;
    m_position += m_velocity * dt;
    m_velocityTarget = {0.0f, 0.0f};
}

void EntityBody::haltMotionInDirection(px::Vec2i dir)
{
    if (px::Utils::Numbers::sign(m_velocity.x) == px::Utils::Numbers::sign(dir.x))
    {
        m_velocity.x = 0.0f;
    }
    if (px::Utils::Numbers::sign(m_velocity.y) == px::Utils::Numbers::sign(dir.y))
    {
        m_velocity.y = 0.0f;
    }

    if (px::Utils::Numbers::sign(m_velocityTarget.x) == px::Utils::Numbers::sign(dir.x))
    {
        m_velocityTarget.x = 0.0f;
    }
    if (px::Utils::Numbers::sign(m_velocityTarget.y) == px::Utils::Numbers::sign(dir.y))
    {
        m_velocityTarget.y = 0.0f;
    }
}
