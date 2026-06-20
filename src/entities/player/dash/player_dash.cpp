#include "player_dash.hpp"
#include "px/utils/interpolation.hpp"

PlayerDash::PlayerDash() { m_dashTimer.setDurationInMilliseconds(200); }

void PlayerDash::dash(Direction direction)
{
    if (m_state == State::Idle)
    {
        m_dashTimer.restart();
        m_state            = State::Dashing;
        m_currentDirection = direction;
    }
}

void PlayerDash::update(const EntityUpdateContext &context)
{
    switch (m_state)
    {
    case State::Dashing:
    {
        px::Vec2i dir  = m_directions.at(m_currentDirection);
        float vel      = px::Utils::Interpolation::lerp(10.0f, 2.0f, m_dashTimer.getProgress());
        m_dashVelocity = dir.toFloat() * vel;

        m_dashTimer.update(context.time.dt);

        if (m_dashTimer.completed())
        {
            m_state = State::Idle;
        }
    }
    break;
    case State::Idle:
        m_dashVelocity = {};

        break;
    }
}
