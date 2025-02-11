#include "input_manager.hpp"

#include <string>
#include <cmath>
#include <iostream>

#include "../logger/logger.hpp"

Vec2<float> InputManager::getJoystickPos() const
{
    auto get_div = [&](int value)
    {
        return value < 0 ? 32768 : 32767;
    };

    const float x_div = get_div(m_gamepad_pos.x);
    const float y_div = get_div(m_gamepad_pos.y);

    return Vec2<float>(m_gamepad_pos.x / x_div, m_gamepad_pos.y / y_div);
}

void InputManager::update_gamepad()
{
    if (std::abs(m_gamepad_pos.x) <= m_gamepad_deadzone &&
        std::abs(m_gamepad_pos.y) <= m_gamepad_deadzone)
    {
        m_gamepad_pos.x = 0;
        m_gamepad_pos.y = 0;
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
    case 0:
        m_gamepad_pos.x = value;
        break;
    case 1:
        m_gamepad_pos.y = value;
        break;
    }
}

void InputManager::assign_gamepad(int id)
{
    bool gamepad_assigned = m_gamepads.find(id) != m_gamepads.end();
    if (gamepad_assigned)
    {
        const char *p_gamepad_name = SDL_GetGamepadName(m_gamepads[id]);
        std::string gamepad_name = p_gamepad_name ? p_gamepad_name : "Unknown gamepad";
        Log::log(Log::Type::Warn, "InputManager", "Gamepad: [" + std::to_string(id) + "] already assigned");

        return;
    }

    SDL_Gamepad *gamepad = SDL_OpenGamepad(id);
    m_gamepads[id] = gamepad;

    current_gamepad = id;

    std::string gamepad_name = SDL_GetGamepadName(gamepad);
    Log::log(Log::Type::Info, "InputManager", "Assigned gamepad: [" + std::to_string(id) + "] " + gamepad_name);
    Log::log(Log::Type::Info, "InputManager", "Gamepads connected: " + std::to_string(m_gamepads.size()));
}

void InputManager::remove_gamepad(int id)
{
    bool gamepad_assigned = m_gamepads.find(id) != m_gamepads.end();
    if (!gamepad_assigned)
    {
        Log::log(Log::Type::Warn, "InputManager", "No gamepad assigned at: " + std::to_string(id));
        return;
    }

    SDL_Gamepad *gamepad = m_gamepads[id];
    const char *p_gamepad_name = SDL_GetGamepadName(gamepad);
    std::string gamepad_name = p_gamepad_name ? p_gamepad_name : "Unknown gamepad";

    SDL_CloseGamepad(gamepad);
    m_gamepads.erase(id);

    Log::log(Log::Type::Info, "InputManager", "Removed gamepad: [" + std::to_string(id) + "] " + gamepad_name);
    Log::log(Log::Type::Info, "InputManager", "Gamepads left: " + std::to_string(m_gamepads.size()));
}