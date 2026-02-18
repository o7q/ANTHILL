#pragma once

#include <SDL3/SDL_timer.h>
#include <chrono>

class TimeHandler
{
  public:
    TimeHandler() = default;
    TimeHandler(const TimeHandler &other) = delete;
    TimeHandler &operator=(const TimeHandler &other) = delete;

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
    }

    void setSpeedMultiplier(float speed_multiplier)
    {
        m_speed_multiplier = speed_multiplier;
    }

    float getFramerate() const { return m_fps; }
    float getDeltaTime() const { return m_dt; }

  private:
    std::chrono::steady_clock::time_point m_frame_start;

    const float m_max_dt = 3.0f;
    float m_target_fps = 60.0f;
    float m_fps = 60.0f;
    float m_dt = 1.0f;

    float m_speed_multiplier = 1.0f;
};
