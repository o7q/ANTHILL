#include "input_manager.hpp"

#include <SDL3/SDL.h>

void InputManager::update()
{
    for (auto &button : m_buttons)
    {
        button.second.update();
    }
}

void InputManager::poll(SDL_Event event)
{
    auto poll_buttons = [&](int generic_button, IButton::PollType poll_type, bool down)
    {
        for (auto &button : m_buttons)
            button.second.poll(generic_button, poll_type, down);
    };

    switch (event.type)
    {
    case SDL_EVENT_KEY_DOWN:
        poll_buttons(event.key.key, IButton::PollType::Keyboard, true);
        m_controller_mode = false;
        break;

    case SDL_EVENT_KEY_UP:
        poll_buttons(event.key.key, IButton::PollType::Keyboard, false);
        break;

    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        poll_buttons(event.gbutton.button, IButton::PollType::Controller, true);
        m_controller_mode = true;
        break;

    case SDL_EVENT_GAMEPAD_BUTTON_UP:
        poll_buttons(event.gbutton.button, IButton::PollType::Controller, false);
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        poll_buttons(event.button.button, IButton::PollType::Mouse, true);
        m_controller_mode = false;
        break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
        poll_buttons(event.button.button, IButton::PollType::Mouse, false);
        break;
    }
}