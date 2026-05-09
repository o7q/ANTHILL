#pragma once

#include "core/math/interpolation.hpp"
#include "core/timer/timer.hpp"

class SpeedChanger
{
  private:
    enum class State
    {
        Idle,
        Start,
        Hold,
        End
    };

  public:
    struct Settings
    {
        float startLength = 0.0f;

        float holdSpeed  = 1.0f;
        float holdLength = 0.0f;

        float endLength = 0.0f;
    };

  public:
    void startTransition(Settings settings)
    {
        m_startTimer.setDurationInSeconds(settings.startLength);
        m_holdTimer.setDurationInSeconds(settings.holdLength);
        m_endTimer.setDurationInSeconds(settings.endLength);

        m_startTimer.restart();
        m_holdTimer.restart();
        m_endTimer.restart();

        m_state    = State::Start;
        m_settings = settings;
    }

    void stopTransition()
    {
        m_state        = State::Idle;
        m_currentSpeed = 1.0f;
    }

    void setSpeed(float speed) { m_currentSpeed = speed; }

    void update(float dt)
    {
        switch (m_state)
        {
        case State::Start:
        {
            if (m_startTimer.completed())
            {
                m_state        = State::Hold;
                m_currentSpeed = m_settings.holdSpeed;
                return;
            }

            m_currentSpeed =
                Math::Interpolation::easeOutCubic(1.0f, m_settings.holdSpeed, m_startTimer.getProgress());

            m_startTimer.update(dt);
        }
        break;
        case State::Hold:
        {
            if (m_holdTimer.completed())
            {
                m_state = State::End;
            }

            m_holdTimer.update(dt);
        }
        break;
        case State::End:
        {
            if (m_endTimer.completed())
            {
                m_state = State::Idle;
            }

            m_currentSpeed =
                Math::Interpolation::smoothStep(m_settings.holdSpeed, 1.0f, m_endTimer.getProgress());

            m_endTimer.update(dt);
        }
        break;
        default:
            m_currentSpeed = 1.0f;
            break;
        }
    }

    float getCurrentSpeed() const { return m_currentSpeed; }
    State getTransitionState() const { return m_state; }

  private:
    Settings m_settings;

    State m_state = State::Idle;

    Timer m_startTimer;
    Timer m_holdTimer;
    Timer m_endTimer;

    float m_currentSpeed = 1.0f;
};