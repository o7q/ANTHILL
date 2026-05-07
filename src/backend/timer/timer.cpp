#include "timer.hpp"

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
        m_clock     = 0.0f;
        m_completed = true;

        if (m_mode == Mode::Once)
        {
            m_active = false;
        }
    }
    else
    {
        m_clock += dt;
        m_progress = m_clock / k;
    }
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

void Timer::setDurationInSeconds(float seconds) { m_durationInSeconds = seconds; }
void Timer::setDurationInMilliseconds(float milliseconds) { m_durationInSeconds = milliseconds / 1000.0f; }
