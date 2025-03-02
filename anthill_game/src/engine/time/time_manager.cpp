#include "time_manager.hpp"

TimeManager::TimeManager()
{
    for (int i = 0; i < m_dt_iterations; ++i)
    {
        m_dt_history[i] = 1.0f;
    }
}

void TimeManager::frameStart()
{
    m_frame_start = std::chrono::steady_clock::now();
}

void TimeManager::frameEnd()
{
    m_frame_end = std::chrono::steady_clock::now();
}

void TimeManager::setSpeed(float speed)
{
    m_speed_modifier = speed;
}

void TimeManager::completeFrame()
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
    m_dt = 60.0f / m_fps * m_speed_modifier;

    m_dt_history[m_dt_history_index] = m_dt;

    float sum = 0.0f;
    for (int i = 0; i < m_dt_iterations; ++i)
    {
        sum += m_dt_history[i];
    }

    if (m_dt_history_index >= m_dt_iterations)
    {
        m_dt_history_index = 0;
    }
    else
    {
        ++m_dt_history_index;
    }

    m_dt_smoothed = sum / m_dt_iterations;
}

void TimeManager::setTargetFramerate(float target_framerate)
{
    m_target_fps = target_framerate;
}