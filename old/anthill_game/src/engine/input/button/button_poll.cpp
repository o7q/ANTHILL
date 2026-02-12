#include "button.hpp"

void IButton::poll(int generic_button, PollType poll_type, bool down)
{
    switch (poll_type)
    {
    case PollType::Keyboard:
        if (generic_button == m_keycode && m_key_assigned)
            m_down = down;
        break;
    case PollType::GamepadButton:
        if (generic_button == m_gamepad_button && m_gamepad_button_assigned)
            m_down = down;
        break;
    case PollType::GamepadTrigger:
        if (generic_button == m_gamepad_trigger && m_gamepad_trigger_assigned)
            m_down = down;
        break;
    case PollType::Mouse:
        if (generic_button == m_mouse_button && m_mouse_button_assigned)
            m_down = down;
        break;
    }
}