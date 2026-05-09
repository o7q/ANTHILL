#include "window.hpp"

#include "core/logger/logger.hpp"
#include "core/viewport/viewport.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>

Window::Window(const std::string &name, Vec2u windowSize, Vec2u viewportSize)
    : m_window(SDL_CreateWindow(name.c_str(), windowSize.x, windowSize.y, SDL_WINDOW_RESIZABLE)),
      m_viewport(m_window, viewportSize)
{
    Logger::info("Window::Window()", "Successfully initialized the window!");
}

Window::~Window() { SDL_DestroyWindow(m_window); }

void Window::frameStart() { m_time.frameStart(); }
void Window::frameEnd() { m_time.frameEnd(); }

void Window::update()
{
    m_sound.update();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_running = false;
        }

        m_input.poll(event);
    }

    m_input.update();

    int winX, winY;
    SDL_GetWindowSizeInPixels(m_window, &winX, &winY);
    m_size = Vec2i(winX, winY).toUnsignedInt();

    m_aspectRatio = static_cast<float>(winX) / winY;

    m_viewport.recalculatePresentRect(m_size, m_aspectRatio);
}

void Window::clear() { m_viewport.clear(); }
void Window::present() { m_viewport.present(); }
