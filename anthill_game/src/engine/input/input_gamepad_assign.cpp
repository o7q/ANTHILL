#include "input_manager.hpp"

#include <string>

#include "../logger/logger.hpp"

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