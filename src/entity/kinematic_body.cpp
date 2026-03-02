#include "kinematic_body.hpp"

#include "utils/math/numbers.hpp"

void KinematicBody::haltMotionInDirection(int dirX, int dirY)
{
    if (Utils::Math::Numbers::sign(m_force.x) ==
        Utils::Math::Numbers::sign(dirX))
    {
        m_force.x = 0.0f;
    }
    if (Utils::Math::Numbers::sign(m_force.y) ==
        Utils::Math::Numbers::sign(dirY))
    {
        m_force.y = 0.0f;
    }
    if (Utils::Math::Numbers::sign(m_velocity.x) ==
        Utils::Math::Numbers::sign(dirX))
    {
        m_velocity.x = 0.0f;
    }
    if (Utils::Math::Numbers::sign(m_velocity.y) ==
        Utils::Math::Numbers::sign(dirY))
    {
        m_velocity.y = 0.0f;
    }
}
