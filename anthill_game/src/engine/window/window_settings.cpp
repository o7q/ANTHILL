#include "window.hpp"

#include "../logger/logger.hpp"

void Window::showCursor(bool value)
{
    m_cursor_visible = value;
    value ? SDL_ShowCursor() : SDL_HideCursor();
}

void Window::setCursor(SDL_Surface* cursor_surface)
{
    if (m_cursor != nullptr)
    {
        SDL_SetCursor(NULL);
        SDL_DestroyCursor(m_cursor);
    }
    m_cursor = SDL_CreateColorCursor(cursor_surface, 0, 0);
    SDL_SetCursor(m_cursor);
}

void Window::clearCursorImage()
{
    if (m_cursor != nullptr)
    {
        SDL_DestroyCursor(m_cursor);
    }
    SDL_SetCursor(NULL);
}

void Window::setFullscreen(bool value)
{
    SDL_SetWindowFullscreen(m_window, value);
    m_is_fullscreen = value;
    
    Log::log(Log::Type::Info, "Window", "Fullscreen: " + std::to_string(value));
}