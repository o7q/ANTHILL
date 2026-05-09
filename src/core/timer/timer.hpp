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
    void update(float dt);
    void restart();
    void stop();

    void setDurationInSeconds(float seconds);
    void setDurationInMilliseconds(float milliseconds);

    bool active() const { return m_active; }
    bool completed() const { return m_completed; }

    void setMode(Mode mode) { m_mode = mode; }

    float getProgress() const { return m_progress; }

  private:
    float m_durationInSeconds = 1.0f;
    float m_clock             = 0.0f;
    float m_progress          = 0.0f;

    bool m_active    = false;
    bool m_completed = false;

    Mode m_mode = Mode::Once;
};
