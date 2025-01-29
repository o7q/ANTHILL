#include "input_manager.hpp"

#include <SDL3/SDL.h>

void InputManager::poll(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_EVENT_KEY_DOWN:
        handle_keydown(event.key);
        m_controller_mode = false;
        break;
    case SDL_EVENT_KEY_UP:
        handle_keyup(event.key);
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        handle_mousedown(event.button);
        m_controller_mode = false;
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        handle_mouseup(event.button);
        break;
    }
}