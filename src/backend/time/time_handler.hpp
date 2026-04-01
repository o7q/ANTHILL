#pragma once

#include <SDL3/SDL_timer.h>
#include <chrono>

class TimeHandler
{
  public:
    TimeHandler() = default;
    TimeHandler(const TimeHandler &other) = delete;
    TimeHandler &operator=(const TimeHandler &other) = delete;
    ~TimeHandler() = default;

    void frameStart();
    void frameEnd();

    void setSpeedMultiplier(float speed_multiplier)
    {
        m_speed_multiplier = speed_multiplier;
    }

    void setMaxFPS(float max_fps) { m_max_fps = max_fps; }

    float getFPS() const { return m_fps; }
    float getDT() const { return m_dt; }

  private:
    std::chrono::steady_clock::time_point m_frame_start;

    const float m_max_dt = 5.0f;
    float m_max_fps = 60.0f;
    float m_fps = 60.0f;
    float m_dt = 1.0f;

    const float m_dt_base_fps = 60.0f;

    float m_speed_multiplier = 1.0f;
};
