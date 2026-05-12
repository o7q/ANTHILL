#include "player_jetpack.hpp"

void PlayerJetpack::start()
{
    if (m_state == State::Idle)
    {
        m_fuelTimer.restart();
        m_state = State::Active;
    }
}

void PlayerJetpack::stop() { m_state = State::Idle; }

void PlayerJetpack::update(EntityBody &body, float dt)
{
    switch (m_state)
    {
    case State::Active:
        if (m_fuelTimer.completed())
        {
            m_state = State::Drained;
        }

        body.setGravity(0.0f);
        m_fuelTimer.update(dt);
        break;
        case State::Drained:
        body.setGravity(2.0f);
        break;
    default:
        break;
    }
}
