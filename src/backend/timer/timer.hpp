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
    void setDurationInSeconds(float seconds);
    void setDurationInMilliseconds(float milliseconds);

    void update(float dt);

    void restart();

    void stop();

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
