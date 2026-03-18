#include "window.hpp"

#include "backend/viewport/viewport.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>

Window::Window(Vec2<unsigned int> windowSize, Vec2<unsigned int> viewportSize)
    : m_window(SDL_CreateWindow("ANTHILL", windowSize.x, windowSize.y,
                                SDL_WINDOW_RESIZABLE)),
      m_viewport(nullptr, viewportSize.x, viewportSize.y)
{
}

Window::~Window() { SDL_DestroyWindow(m_window); }

void Window::frameStart()
{
    m_timeHandler.frameStart();

    m_viewport.clear();
    m_eventHandler.resetEvents();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        m_eventHandler.poll(event);
        m_inputHandler.poll(event);
    }

    m_inputHandler.update();

    int winX, winY;
    SDL_GetWindowSizeInPixels(m_window, &winX, &winY);
    m_size.x = winX;
    m_size.y = winY;

    m_aspectRatio = static_cast<float>(winX) / winY;

    m_viewport.recalculatePresentRect(m_size, m_aspectRatio);
}

void Window::frameEnd() { m_timeHandler.frameEnd(); }

void Window::render() { m_viewport.render(); }
