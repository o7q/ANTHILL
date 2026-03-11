#include "entity_kinetic_body.hpp"

#include "utils/math/numbers.hpp"

void EntityKineticBody::haltMotionInDirection(int dirX, int dirY)
{
    Vec2<float> force = m_body.getForce();
    if (Utils::Math::Numbers::sign(force.x) == Utils::Math::Numbers::sign(dirX))
    {
        force.x = 0.0f;
    }
    if (Utils::Math::Numbers::sign(force.y) == Utils::Math::Numbers::sign(dirY))
    {
        force.y = 0.0f;
    }
    m_body.setForce(force.x, force.y);

    Vec2<float> vel = m_body.getVelocity();
    if (Utils::Math::Numbers::sign(vel.x) == Utils::Math::Numbers::sign(dirX))
    {
        vel.x = 0.0f;
    }
    if (Utils::Math::Numbers::sign(vel.y) == Utils::Math::Numbers::sign(dirY))
    {
        vel.y = 0.0f;
    }
    m_body.setVelocity(vel.x, vel.y);
}

void EntityKineticBody::update(float dt)
{
    m_lastPos = getPosition();

    if (std::abs(m_body.getVelocity().x) < 0.01f)
    {
        m_body.setVelocityX(0);
    }
    if (std::abs(m_body.getVelocity().y) < 0.01f)
    {
        m_body.setVelocityY(0);
    }

    m_body.integrate(dt);
}
