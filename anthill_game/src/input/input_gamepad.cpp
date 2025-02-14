#include "input_manager.hpp"

#include <string>
#include <cmath>

#include "../logger/logger.hpp"

Vec2<float> InputManager::getJoystickPos(int index) const
{
    Vec2<int> joystick_pos = index == 0 ? m_left_joystick_pos : m_right_joystick_pos;

    auto get_div = [&](int value)
    {
        return value < 0 ? 32768 : 32767;
    };

    const float x_div = get_div(joystick_pos.x);
    const float y_div = get_div(joystick_pos.y);

    return Vec2<float>(joystick_pos.x / x_div, joystick_pos.y / y_div);
}

void InputManager::rumbleGamepad(Uint16 low_frequency, Uint16 high_frequency, Uint32 duration)
{
    if (m_active_gamepad == -1)
    {
        return;
    }

    SDL_RumbleGamepad(m_gamepads[m_active_gamepad], low_frequency, high_frequency, duration);
}

void InputManager::update_joystick(int index)
{
    Vec2<int> joystick_pos = index == 0 ? m_left_joystick_pos : m_right_joystick_pos;

    if (std::abs(joystick_pos.x) <= m_gamepad_deadzone &&
        std::abs(joystick_pos.y) <= m_gamepad_deadzone)
    {
        joystick_pos.x = 0;
        joystick_pos.y = 0;
    }
    else if (!m_gamepad_mode)
    {
        m_gamepad_mode = true;
        Log::log(Log::Type::Info, "InputManager", "Gamepad mode enabled");
    }
}

void InputManager::poll_gamepad(int value, int axis)
{
    switch (axis)
    {
    case SDL_GAMEPAD_AXIS_LEFTX:
        m_left_joystick_pos.x = value;
        break;
    case SDL_GAMEPAD_AXIS_LEFTY:
        m_left_joystick_pos.y = value;
        break;
    case SDL_GAMEPAD_AXIS_RIGHTX:
        m_right_joystick_pos.x = value;
        break;
    case SDL_GAMEPAD_AXIS_RIGHTY:
        m_right_joystick_pos.y = value;
        break;
    }
}

std::string InputManager::get_gamepad_name(SDL_Gamepad *gamepad)
{
    const char *p_gamepad_name = SDL_GetGamepadName(gamepad);
    return p_gamepad_name ? p_gamepad_name : "Unknown gamepad";
}

void InputManager::assign_gamepad(int id)
{
    bool gamepad_assigned = m_gamepads.find(id) != m_gamepads.end();
    if (gamepad_assigned)
    {
        Log::log(Log::Type::Warn, "InputManager", "Gamepad: [" + std::to_string(id) + "] " + get_gamepad_name(m_gamepads[id]) + " - already assigned");

        return;
    }

    SDL_Gamepad *gamepad = SDL_OpenGamepad(id);
    m_gamepads[id] = gamepad;

    m_active_gamepad = id;

    Log::log(Log::Type::Info, "InputManager", "Assigned gamepad: [" + std::to_string(id) + "] " + get_gamepad_name(gamepad));
    Log::log(Log::Type::Info, "InputManager", "Gamepads connected: " + std::to_string(m_gamepads.size()));
}

void InputManager::remove_gamepad(int id, bool erase_from_map)
{
    bool gamepad_assigned = m_gamepads.find(id) != m_gamepads.end();
    if (!gamepad_assigned)
    {
        Log::log(Log::Type::Warn, "InputManager", "No gamepad assigned at: " + std::to_string(id));
        return;
    }

    SDL_Gamepad *gamepad = m_gamepads[id];
    std::string gamepad_name = get_gamepad_name(gamepad);

    SDL_CloseGamepad(gamepad);

    if (erase_from_map)
    {
        m_gamepads.erase(id);
    }

    m_active_gamepad = -1;

    Log::log(Log::Type::Info, "InputManager", "Removed gamepad: [" + std::to_string(id) + "] " + gamepad_name);
    Log::log(Log::Type::Info, "InputManager", "Gamepads left: " + std::to_string(m_gamepads.size()));
}