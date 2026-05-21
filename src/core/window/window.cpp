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

void Window::frameStart()
{
    m_time.frameStart();
    m_viewport.clear();

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
    m_sound.update(m_time.getInfo());

    int winSizeX, winSizeY;
    SDL_GetWindowSizeInPixels(m_window, &winSizeX, &winSizeY);
    m_size = Vec2i(winSizeX, winSizeY).toUnsignedInt();

    m_aspectRatio = static_cast<float>(winSizeX) / winSizeY;

    m_viewport.recalculatePresentRect(m_size, m_aspectRatio);
}

void Window::frameEnd()
{
    m_viewport.present();
    m_time.frameEnd();
}
