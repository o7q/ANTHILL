#include "kinetic_body.hpp"

#include "math/numbers.hpp"

void KineticBody::haltMotionInDirection(int dirX, int dirY)
{
    Vec2<float> force = m_body.getForce();
    if (Math::Numbers::sign(force.x) == Math::Numbers::sign(dirX))
    {
        force.x = 0.0f;
    }
    if (Math::Numbers::sign(force.y) == Math::Numbers::sign(dirY))
    {
        force.y = 0.0f;
    }
    m_body.setForce(force.x, force.y);

    Vec2<float> vel = m_body.getVelocity();
    if (Math::Numbers::sign(vel.x) == Math::Numbers::sign(dirX))
    {
        vel.x = 0.0f;
    }
    if (Math::Numbers::sign(vel.y) == Math::Numbers::sign(dirY))
    {
        vel.y = 0.0f;
    }
    m_body.setVelocity(vel.x, vel.y);
}

void KineticBody::update(float dt)
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

    // Vec2<float> vel =
    //     m_body.getVelocity().clamp(Vec2<float>(0, 0), m_maxVelocity);
    // m_body.setVelocity(vel.x, vel.y);

    m_body.integrate(dt);
}
