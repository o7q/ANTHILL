#pragma once

class Timer
{
  public:
    enum class Mode
    {
        Once,
        Repeat
    };

  public:
    void setDurationInSeconds(float seconds) { m_durationInSeconds = seconds; }
    void setDurationInMilliseconds(float milliseconds)
    {
        m_durationInSeconds = milliseconds / 1000.0f;
    }

    void update(float dt)
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

    void restart()
    {
        m_clock = 0.0f;
        m_active = true;
        m_completed = false;
    }

    void stop()
    {
        m_clock = 0.0f;
        m_active = false;
        m_completed = false;
    }

    bool active() const { return m_active; }
    bool completed() const { return m_completed; }

    void setMode(Mode mode) { m_mode = mode; }

  private:
    float m_durationInSeconds = 1.0f;
    float m_clock = 0.0f;

    bool m_completed = false;
    bool m_active = false;

    Mode m_mode = Mode::Once;
};
