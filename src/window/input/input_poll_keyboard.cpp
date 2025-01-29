#include "input_manager.hpp"

#include <SDL3/SDL.h>

void InputManager::handle_keydown(SDL_KeyboardEvent event)
{
    switch (event.key)
    {
    case SDLK_W:
    case SDLK_UP:
        m_up.setDown(true);
        break;
    case SDLK_S:
    case SDLK_DOWN:
        m_down.setDown(true);
        break;
    case SDLK_A:
    case SDLK_LEFT:
        m_left.setDown(true);
        break;
    case SDLK_D:
    case SDLK_RIGHT:
        m_right.setDown(true);
        break;
    case SDLK_1:
        m_debug1.setDown(true);
        break;
    case SDLK_2:
        m_debug2.setDown(true);
        break;
    case SDLK_3:
        m_debug3.setDown(true);
        break;
    }
}

void InputManager::handle_keyup(SDL_KeyboardEvent event)
{
    switch (event.key)
    {
    case SDLK_W:
    case SDLK_UP:
        m_up.setDown(false);
        break;
    case SDLK_S:
    case SDLK_DOWN:
        m_down.setDown(false);
        break;
    case SDLK_A:
    case SDLK_LEFT:
        m_left.setDown(false);
        break;
    case SDLK_D:
    case SDLK_RIGHT:
        m_right.setDown(false);
        break;
    case SDLK_1:
        m_debug1.setDown(false);
        break;
    case SDLK_2:
        m_debug2.setDown(false);
        break;
    case SDLK_3:
        m_debug3.setDown(false);
        break;
    }
}