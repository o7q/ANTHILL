#include "window.hpp"

#include "event_handler.hpp"
#include "input_handler.hpp"
#include "time_handler.hpp"
#include "vec.hpp"
#include "viewport.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <algorithm>
#include <cstddef>

Window::Window(Vec2<unsigned int> windowSize, Vec2<unsigned int> viewportSize)
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    m_window = SDL_CreateWindow("ANTHILL", windowSize.x, windowSize.y,
                                SDL_WINDOW_RESIZABLE);
    m_renderer = SDL_CreateRenderer(m_window, NULL);

    m_viewport.init(m_renderer,
                    Vec2<unsigned int>(viewportSize.x, viewportSize.y));
}
Window::~Window()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void Window::frameStart()
{
    m_timeHandler.frameStart();
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

    recalculate_viewport_rect();
}

void Window::frameEnd() { m_timeHandler.frameEnd(); }

void Window::render()
{
    SDL_RenderClear(m_renderer);

    m_viewport.updatePixelChanges();
    SDL_RenderTexture(m_renderer, m_viewport.getSDLTexture(), NULL,
                      &m_viewportRect);

    SDL_RenderPresent(m_renderer);

    SDL_Delay(1);
}

Vec2<unsigned int> Window::windowToViewportPosition(Vec2<float> windowPosition)
{
    Vec2<unsigned int> viewportSize = m_viewport.getSize();

    windowPosition.x -= m_viewportRect.x;
    windowPosition.y -= m_viewportRect.y;

    float pixelSize = m_viewportRect.w / viewportSize.x;
    windowPosition.x /= pixelSize;
    windowPosition.y /= pixelSize;

    windowPosition.x = std::clamp(windowPosition.x, 0.0f,
                                  static_cast<float>(viewportSize.x) - 1);
    windowPosition.y = std::clamp(windowPosition.y, 0.0f,
                                  static_cast<float>(viewportSize.y) - 1);

    return Vec2<unsigned int>(windowPosition.x, windowPosition.y);
}

void Window::recalculate_viewport_rect()
{
    float viewport_aspect = m_viewport.getAspectRatio();
    if (m_aspectRatio > viewport_aspect)
    {
        m_viewportRect.w = m_size.x / m_aspectRatio * viewport_aspect;
        m_viewportRect.h = m_size.y;
    }
    else
    {
        m_viewportRect.w = m_size.x;
        m_viewportRect.h = m_size.y * m_aspectRatio / viewport_aspect;
    }
    m_viewportRect.x = m_size.x / 2.0f - m_viewportRect.w / 2.0f;
    m_viewportRect.y = m_size.y / 2.0f - m_viewportRect.h / 2.0f;
}