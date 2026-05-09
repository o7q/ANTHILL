#include "player_dash.hpp"

#include "math/angle.hpp"
#include "math/interpolation.hpp"
#include <algorithm>

PlayerDash::PlayerDash()
{
    m_startTimer.setDurationInMilliseconds(0);
    m_dashTimer.setDurationInMilliseconds(500);
}

void PlayerDash::start(Angle angle)
{
    if (m_state == State::Idle)
    {
        m_startTimer.restart();
        m_dashTimer.restart();
        m_state     = State::Charging;
        m_dashAngle = angle.radians();
    }
}

void PlayerDash::stop()
{
    m_state = State::Idle;
    m_startTimer.stop();
    m_dashTimer.stop();
}

void PlayerDash::update(const EntityUpdateContext &context)
{
    switch (m_state)
    {
    case State::Charging:
    {
        m_dashVelocity = {0, 0};
        m_startTimer.update(context.time.dt);

        if (m_startTimer.completed())
        {
            m_state = State::Dashing;
        }
    }
    break;
    case State::Dashing:
    {
        dash_update_velocity();

        m_dashTimer.update(context.time.dt);

        if (m_dashTimer.completed())
        {
            m_state = State::Idle;
        }
    }
    break;
    default:
        break;
    }
}

void PlayerDash::dash_update_velocity()
{
    Vec2f dir = {std::cosf(m_dashAngle), std::sinf(m_dashAngle)};

    Vec2f startVel = dir * 10.0f;
    Vec2f endVel   = dir * 5.0f;

    float velX = Math::Interpolation::easeOutCubic(startVel.x, endVel.x,
                                                   std::clamp(m_dashTimer.getProgress(), 0.0f, 1.0f));
    float velY = Math::Interpolation::easeOutCubic(startVel.y, endVel.y,
                                                   std::clamp(m_dashTimer.getProgress(), 0.0f, 1.0f));

    m_dashVelocity = {velX, velY};
}
