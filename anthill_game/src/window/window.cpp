#include "window.hpp"

#include <string>

#include <SDL3/SDL.h>

Window::Window(const std::string &title, unsigned int width, unsigned int height, unsigned int scale)
{
    m_window_size.x = width;
    m_window_size.y = height;
    m_scale = scale;

    m_window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE);
    m_renderer = SDL_CreateRenderer(m_window, NULL);

    m_render_manager.setRenderer(m_renderer);
    m_render_manager.setScale(scale);

    SDL_SetRenderLogicalPresentation(m_renderer, scale, scale, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

Window::~Window()
{
    if (m_renderer != nullptr)
        SDL_DestroyRenderer(m_renderer);
    if (m_window != nullptr)
        SDL_DestroyWindow(m_window);
    if (m_cursor != nullptr)
        SDL_DestroyCursor(m_cursor);
}

void Window::update()
{
    SDL_GetWindowSize(m_window, &m_window_size.x, &m_window_size.y);

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // poll inputs
        m_input_manager.poll(event);

        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            m_closed = true;
            break;
        default:
            break;
        }
    }

    m_input_manager.update();

    // update internal mouse state
    m_input_manager.updateMouse(m_window_size.x, m_window_size.y, m_scale);
}

void Window::clear()
{
    SDL_RenderClear(m_renderer);
}

void Window::display()
{
    SDL_RenderPresent(m_renderer);
}