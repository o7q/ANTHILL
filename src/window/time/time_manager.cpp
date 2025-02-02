#include "time_manager.hpp"

void TimeManager::frameStart()
{
    m_frame_start = std::chrono::steady_clock::now();
}

void TimeManager::frameEnd()
{
    m_frame_end = std::chrono::steady_clock::now();
}

void TimeManager::delay()
{
    const float frame_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(m_frame_end - m_frame_start).count();

    const float target_frame_seconds = 1.0f / m_target_fps;
    if (frame_seconds < target_frame_seconds)
    {
        const float frame_delay = (target_frame_seconds - frame_seconds) * 1000.0f;
        SDL_Delay(static_cast<Uint32>(frame_delay));
    }

    const std::chrono::steady_clock::time_point delayed_frame_end = std::chrono::steady_clock::now();
    const float total_frame_seconds = std::chrono::duration<float>(delayed_frame_end - m_frame_end).count();

    m_fps = 1.0f / (total_frame_seconds + frame_seconds);
    m_dt = 60.0f / m_fps;
}

void TimeManager::setTargetFramerate(float target_framerate)
{
    m_target_fps = target_framerate;
}