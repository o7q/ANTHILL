#include "input_manager.hpp"

#include <SDL3/SDL.h>

void InputManager::handle_mousedown(SDL_MouseButtonEvent event)
{
    switch (event.button)
    {
    case SDL_BUTTON_LEFT:
        m_action1.setDown(true);
        break;
    }
}
void InputManager::handle_mouseup(SDL_MouseButtonEvent event)
{
    switch (event.button)
    {
    case SDL_BUTTON_LEFT:
        m_action1.setDown(false);
        break;
    }
}