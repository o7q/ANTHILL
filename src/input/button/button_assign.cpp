#include "button.hpp"

void IButton::assignKey(int keycode)
{
    m_keycode = keycode;
    m_key_assigned = true;
}

void IButton::unassignKey()
{
    m_key_assigned = false;
}

void IButton::assignGamepadButton(int gamepad_button)
{
    m_gamepad_button = gamepad_button;
    m_gamepad_button_assigned = true;
}

void IButton::unassignGamepadButton()
{
    m_gamepad_button_assigned = false;
}

void IButton::assignMouseButton(int mouse_button)
{
    m_mouse_button = mouse_button;
    m_mouse_button_assigned = true;
}

void IButton::unassignMouseButton()
{
    m_mouse_button_assigned = false;
}