#include "timer.hpp"

void Timer::setDurationInSeconds(float seconds) { m_durationInSeconds = seconds; }
void Timer::setDurationInMilliseconds(float milliseconds) { m_durationInSeconds = milliseconds / 1000.0f; }

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

    const float k = 60.0f * m_durationInSeconds;
    if (m_clock >= k)
    {
        m_completed = true;

        switch (m_mode)
        {
        case Mode::Repeat:
            m_clock = 0.0f;
            break;
        case Mode::Once:
            m_clock  = 0.0f;
            m_active = false;
            break;
        }
    }

    m_clock += dt;
    m_progress = m_clock / k;
}

void Timer::restart()
{
    m_clock     = 0.0f;
    m_active    = true;
    m_completed = false;
}

void Timer::stop()
{
    m_clock     = 0.0f;
    m_active    = false;
    m_completed = false;
}
