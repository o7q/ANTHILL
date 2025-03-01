#include "input_manager.hpp"

#include <cmath>

Vec2<float> InputManager::getJoystickPos(int index) const
{
    if (index != 0 && index != 1)
    {
        return Vec2<float>(0.0f, 0.0f);
    }

    auto get_div = [&](int value)
    {
        return value < 0 ? 32768 : 32767;
    };

    const float x_div = get_div(m_joystick_pos[index].x);
    const float y_div = get_div(m_joystick_pos[index].y);

    return Vec2<float>(m_joystick_pos[index].x / x_div, m_joystick_pos[index].y / y_div);
}

Vec2<float> InputManager::getJoystickDirection(int index) const
{
    if (index != 0 && index != 1)
    {
        return Vec2<float>(0.0f, 0.0f);
    }

    float x = m_joystick_pos[index].x;
    float y = m_joystick_pos[index].y;

    float m = std::sqrt(x * x + y * y);

    float epsilon = 0.00001f;
    if (m <= epsilon)
    {
        return Vec2<float>(0.0f, 0.0f);
    }

    return Vec2<float>(x / m, y / m);
}

float InputManager::getTriggerValue(int index)
{
    if (index != 0 && index != 1)
    {
        return 0.0f;
    }

    return m_trigger_value[index] / 32767.0f;
}

bool InputManager::joystickMoved(int index) const
{
    return m_joystick_pos[index].x != 0 || m_joystick_pos[index].y != 0;
}

// max 65535
void InputManager::rumbleGamepad(Uint16 low_frequency, Uint16 high_frequency, Uint32 duration)
{
    if (m_gamepads.find(m_active_gamepad) == m_gamepads.end())
    {
        return;
    }

    SDL_RumbleGamepad(m_gamepads[m_active_gamepad], low_frequency, high_frequency, duration);
}

void InputManager::rumbleGamepadTriggers(Uint16 left_rumble, Uint16 right_rumble, Uint32 duration)
{
    if (m_gamepads.find(m_active_gamepad) == m_gamepads.end())
    {
        return;
    }

    SDL_RumbleGamepadTriggers(m_gamepads[m_active_gamepad], left_rumble, right_rumble, duration);
}