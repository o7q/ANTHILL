#pragma once

#include "backend/timer/timer.hpp"
#include "entity/body/entity_body.hpp"
class Jetpack
{
  public:
    enum class State
    {
        Flying,
        Gliding,
        Idle
    };

  public:
    Jetpack() { m_flightTimer.setDurationInMilliseconds(500); }

    void start()
    {
        if (m_state == State::Idle)
        {
            m_flightTimer.restart();
            m_state = State::Flying;
        }
    }

    void stop() { m_state = State::Idle; }

    void update(EntityBody &body, float dt)
    {
        switch (m_state)
        {
        case State::Flying:

            if (m_flightTimer.completed())
            {
                m_state = State::Gliding;
            }

            body.setVelocityTargetY(-20.0f);
            m_flightTimer.update(dt);
            break;
        case State::Gliding:
            body.setVelocityTargetY(-10.0f);
            break;
        default:
            break;
        }
    }

  private:
    State m_state = State::Idle;

    Timer m_flightTimer;
};
