#include "input_manager.hpp"

#include <cmath>

#include "../logger/logger.hpp"

void InputManager::update_joystick(int index)
{
    if (std::abs(m_joystick_pos[index].x) <= m_gamepad_deadzone &&
        std::abs(m_joystick_pos[index].y) <= m_gamepad_deadzone)
    {
        m_joystick_pos[index].x = 0;
        m_joystick_pos[index].y = 0;
    }
    else if (!m_gamepad_mode)
    {
        m_gamepad_mode = true;
        Log::log(Log::Level::Info, "InputManager", "Gamepad mode enabled");
    }
}

void InputManager::poll_gamepad_axis(int value, int axis)
{
    switch (axis)
    {
    case SDL_GAMEPAD_AXIS_LEFTX:
        m_joystick_pos[0].x = value;
        break;
    case SDL_GAMEPAD_AXIS_LEFTY:
        m_joystick_pos[0].y = value;
        break;
    case SDL_GAMEPAD_AXIS_RIGHTX:
        m_joystick_pos[1].x = value;
        break;
    case SDL_GAMEPAD_AXIS_RIGHTY:
        m_joystick_pos[1].y = value;
        break;
    case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
        m_trigger_value[0] = value;
        break;
    case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
        m_trigger_value[1] = value;
        break;
    }
}