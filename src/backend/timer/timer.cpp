#include "timer.hpp"

void Timer::setDurationInSeconds(float seconds)
{
    m_durationInSeconds = seconds;
}
void Timer::setDurationInMilliseconds(float milliseconds)
{
    m_durationInSeconds = milliseconds / 1000.0f;
}

void Timer::update(float dt)
{
    if (m_mode == Mode::Repeat)
    {
        m_completed = false;
    }

    if (!m_active)
    {
        return;
    }

    if (m_clock >= 60.0f * m_durationInSeconds)
    {
        m_completed = true;

        switch (m_mode)
        {
        case Mode::Repeat:
            m_clock = 0.0f;
            break;
        case Mode::Once:
            m_clock = 0.0f;
            m_active = false;
            break;
        }
    }
    m_clock += dt;
}

void Timer::restart()
{
    m_clock = 0.0f;
    m_active = true;
    m_completed = false;
}

void Timer::stop()
{
    m_clock = 0.0f;
    m_active = false;
    m_completed = false;
}
