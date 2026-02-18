#pragma once

#include <SDL3/SDL_timer.h>
#include <chrono>

class TimeHandler
{
  public:
    TimeHandler()
    {
        for (int i = 0; i < m_dt_smoothing_iterations; ++i)
        {
            m_dt_history[i] = 1.0f;
        }
    }

    void frameStart() { m_frame_start = std::chrono::steady_clock::now(); }

    void frameEnd()
    {
        std::chrono::steady_clock::time_point frame_end =
            std::chrono::steady_clock::now();

        const float frame_seconds =
            std::chrono::duration_cast<std::chrono::duration<float>>(
                frame_end - m_frame_start)
                .count();

        const float target_frame_seconds = 1.0f / m_target_fps;
        if (frame_seconds < target_frame_seconds)
        {
            const float frame_delay =
                (target_frame_seconds - frame_seconds) * 1000.0f;
            SDL_Delay(static_cast<Uint32>(frame_delay));
        }

        const std::chrono::steady_clock::time_point delayed_frame_end =
            std::chrono::steady_clock::now();
        const float total_frame_seconds =
            std::chrono::duration<float>(delayed_frame_end - m_frame_start)
                .count();

        m_fps = 1.0f / total_frame_seconds;
        m_dt = 60.0f / m_fps * m_speed_multiplier;
        m_dt = std::clamp(m_dt, 0.0f, m_max_dt);

        m_dt_history[m_dt_history_index] = m_dt;
        m_dt_history_index =
            (m_dt_history_index + 1) % m_dt_smoothing_iterations;

        float sum = 0.0f;
        for (int i = 0; i < m_dt_smoothing_iterations; ++i)
        {
            sum += m_dt_history[i];
        }

        m_dt_smoothed = sum / m_dt_smoothing_iterations;
    }

    void setSpeedMultiplier(float speed_multiplier)
    {
        m_speed_multiplier = speed_multiplier;
    }

    float getFramerate() const { return m_fps; }
    float getDeltaTime() const { return m_dt; }
    float getSmoothedDeltaTime() const { return m_dt_smoothed; }

  private:
    std::chrono::steady_clock::time_point m_frame_start;

    const float m_max_dt = 5.0f;
    static constexpr int m_dt_smoothing_iterations = 60;
    float m_dt_history[m_dt_smoothing_iterations];
    int m_dt_history_index = 0;

    float m_target_fps = 60.0f;
    float m_fps = 60.0f;
    float m_dt = 1.0f;
    float m_dt_smoothed = 1.0f;

    float m_speed_multiplier = 1.0f;
};
