#include "window.hpp"

#include "backend/logger/logger.hpp"
#include "backend/viewport/viewport.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>

Window::Window(const std::string &name, Vec2u windowSize, Vec2u viewportSize)
    : m_window(SDL_CreateWindow(name.c_str(), windowSize.x, windowSize.y,
                                SDL_WINDOW_RESIZABLE)),
      m_viewport(m_window, viewportSize.x, viewportSize.y)
{
    Logger::info("Window::Window()", "Successfully initialized the window!");
}

Window::~Window() { SDL_DestroyWindow(m_window); }

void Window::frameStart()
{
    m_timeHandler.frameStart();

    m_viewport.clear();
    m_soundHandler.update();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_running = false;
        }

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
