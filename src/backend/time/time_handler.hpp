#pragma once

#include "speed_changer.hpp"
#include <chrono>

class TimeHandler
{
  public:
    struct Info
    {
        float dt               = 1.0f;
        float dt_raw           = 1.0f;
        float fps              = 60.0f;
        float speed_multiplier = 1.0f;
    };

  public:
    TimeHandler()                                    = default;
    TimeHandler(const TimeHandler &other)            = delete;
    TimeHandler &operator=(const TimeHandler &other) = delete;
    ~TimeHandler()                                   = default;

    void frameStart();
    void frameEnd();

    SpeedChanger &getSpeedChanger() { return m_speedChanger; }

    void setMaxFPS(float max_fps) { m_max_fps = max_fps; }

    Info getInfo() const { return m_info; }

  private:
    std::chrono::steady_clock::time_point m_frame_start;

    const float m_max_dt      = 5.0f;
    const float m_dt_base_fps = 60.0f;

    float m_max_fps = 60.0f;
    Info m_info;

    SpeedChanger m_speedChanger;
};
