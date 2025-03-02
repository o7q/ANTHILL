#pragma once

#include <chrono>
#include <vector>

#include <SDL3/SDL.h>

class TimeManager
{
public:
    TimeManager();

    void frameStart();
    void frameEnd();

    void completeFrame();

    void setTargetFramerate(float target_framerate);

    void setSpeed(float speed);

    float getFramerate() const { return m_fps; }
    float getDeltaTime() const { return m_dt_smoothed; }

private:
    std::chrono::steady_clock::time_point m_frame_start;
    std::chrono::steady_clock::time_point m_frame_end;

    static constexpr int m_dt_iterations = 5;
    float m_dt_history[m_dt_iterations];
    int m_dt_history_index = 0;
    float m_dt_smoothed = 0.0f;

    float m_target_fps = 60.0f;
    float m_fps = 0.0f;
    float m_dt = 0.0f;

    float m_speed_modifier = 1.0f;
};