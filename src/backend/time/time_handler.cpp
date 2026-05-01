#include "time_handler.hpp"

#include <algorithm>
#include <chrono>
#include <thread>

void TimeHandler::frameStart() { m_frame_start = std::chrono::steady_clock::now(); }

void TimeHandler::frameEnd()
{
    std::chrono::steady_clock::time_point frame_end = std::chrono::steady_clock::now();

    const float frame_seconds =
        std::chrono::duration_cast<std::chrono::duration<float>>(frame_end - m_frame_start).count();

    const float target_frame_seconds = 1.0f / m_max_fps;

    if (frame_seconds < target_frame_seconds)
    {
        const float frame_delay = target_frame_seconds - frame_seconds;
        std::this_thread::sleep_for(std::chrono::duration<float>(frame_delay));
    }

    const std::chrono::steady_clock::time_point delayed_frame_end = std::chrono::steady_clock::now();
    const float total_frame_seconds = std::chrono::duration<float>(delayed_frame_end - m_frame_start).count();

    m_info.fps    = 1.0f / total_frame_seconds;
    m_info.dt_raw = std::clamp(m_dt_base_fps / m_info.fps, 0.0f, m_max_dt);
    m_info.dt     = m_info.dt_raw * m_speed_multiplier;
}
