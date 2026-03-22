#include "kinetic_body.hpp"

#include "math/numbers.hpp"

void KineticBody::haltMotionInDirection(int dirX, int dirY)
{
    if (Math::Numbers::sign(m_force.x) == Math::Numbers::sign(dirX))
    {
        m_force.x = 0.0f;
    }
    if (Math::Numbers::sign(m_force.y) == Math::Numbers::sign(dirY))
    {
        m_force.y = 0.0f;
    }

    if (Math::Numbers::sign(m_velocity.x) == Math::Numbers::sign(dirX))
    {
        m_velocity.x = 0.0f;
    }
    if (Math::Numbers::sign(m_velocity.y) == Math::Numbers::sign(dirY))
    {
        m_velocity.y = 0.0f;
    }
}
