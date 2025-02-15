#include "input_manager.hpp"

#include <SDL3/SDL.h>
#include <iostream>

#include "../logger/logger.hpp"

void InputManager::poll(SDL_Event event)
{
    auto poll_buttons = [&](int generic_button, IButton::PollType poll_type, bool down)
    {
        for (auto &button : m_buttons)
            button.second.poll(generic_button, poll_type, down);
    };

    switch (event.type)
    {
        // KEYBOARD BUTTONS
    case SDL_EVENT_KEY_DOWN:
        poll_buttons(event.key.key, IButton::PollType::Keyboard, true);
        if (m_gamepad_mode)
        {
            m_gamepad_mode = false;
            Log::log(Log::Type::Info, "InputManager", "Gamepad mode disabled");
        }
        break;

    case SDL_EVENT_KEY_UP:
        poll_buttons(event.key.key, IButton::PollType::Keyboard, false);
        break;
        //

        // MOUSE BUTTONS
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        poll_buttons(event.button.button, IButton::PollType::Mouse, true);
        if (m_gamepad_mode)
        {
            m_gamepad_mode = false;
            Log::log(Log::Type::Info, "InputManager", "Gamepad mode disabled");
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
        poll_buttons(event.button.button, IButton::PollType::Mouse, false);
        break;
        //

        // GAMEPAD BUTTONS
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        poll_buttons(event.gbutton.button, IButton::PollType::Controller, true);
        m_active_gamepad = event.gdevice.which;
        if (!m_gamepad_mode)
        {
            m_gamepad_mode = true;
            Log::log(Log::Type::Info, "InputManager", "Gamepad mode enabled");
        }
        break;

    case SDL_EVENT_GAMEPAD_BUTTON_UP:
        poll_buttons(event.gbutton.button, IButton::PollType::Controller, false);
        break;
        //

    case SDL_EVENT_GAMEPAD_AXIS_MOTION:
        poll_gamepad_axis(event.jaxis.value, event.jaxis.axis);
        break;

        // GAMEPAD CONNECT
    case SDL_EVENT_JOYSTICK_ADDED:
        assign_gamepad(event.gdevice.which);
        break;

    case SDL_EVENT_JOYSTICK_REMOVED:
        remove_gamepad(event.gdevice.which, true);
        break;
        //
    }
}