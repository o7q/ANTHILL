#pragma once

#include <chrono>

#include <SDL3/SDL.h>

class TimeManager
{
public:
    void frameStart();
    void frameEnd();

    void delay();

    void setTargetFramerate(float target_framerate);

    float getFramerate() const { return m_fps; }
    float getDeltaTime() const { return m_dt; }

private:
    std::chrono::steady_clock::time_point m_frame_start;
    std::chrono::steady_clock::time_point m_frame_end;

    float m_target_fps = 60.0f;
    float m_fps = 0.0f;
    float m_dt = 0.0f;
};