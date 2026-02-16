#pragma once

#include "event_handler.hpp"
#include "input_hander.hpp"
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

class Window
{
  public:
    Window(Vec2<uint16_t> size)
    {
        SDL_InitSubSystem(SDL_INIT_VIDEO);
        m_window =
            SDL_CreateWindow("ANTHILL", size.x, size.y, SDL_WINDOW_RESIZABLE);
        m_renderer = SDL_CreateRenderer(m_window, NULL);

        m_viewport.init(m_renderer, Vec2<unsigned int>(20, 20));
    }
    ~Window()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    void frameStart()
    {
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

        m_aspect = (float)winX / winY;

        recalculate_viewport_rect();
    }

    void render()
    {
        SDL_RenderClear(m_renderer);

        m_viewport.updateSDLTexture();
        SDL_RenderTexture(m_renderer, m_viewport.getSDLTexture(), NULL,
                          &m_viewportRect);

        SDL_RenderPresent(m_renderer);

        SDL_Delay(1);
    }

    Viewport &getViewport() { return m_viewport; }
    EventHandler &getEventHandler() { return m_eventHandler; }
    InputHandler &getInputHandler() { return m_inputHandler; }

    Vec2<unsigned int> windowToViewportPosition(Vec2<float> windowPosition)
    {
        Vec2<unsigned int> viewportSize = m_viewport.getSize();

        windowPosition.x -= m_viewportRect.x;
        windowPosition.y -= m_viewportRect.y;

        float pixelWidthX = m_viewportRect.w / viewportSize.x;
        float pixelWidthY = m_viewportRect.h / viewportSize.y;
        windowPosition.x /= pixelWidthX;
        windowPosition.y /= pixelWidthY;

        windowPosition.x =
            std::clamp(windowPosition.x, 0.0f, (float)viewportSize.x - 1);
        windowPosition.y =
            std::clamp(windowPosition.y, 0.0f, (float)viewportSize.y - 1);

        return Vec2<unsigned int>(windowPosition.x, windowPosition.y);
    }

  private:
    void recalculate_viewport_rect()
    {
        if (m_aspect > 1.0f)
        {
            m_viewportRect.w = m_size.x / m_aspect;
            m_viewportRect.h = m_size.y;
        }
        else
        {
            m_viewportRect.w = m_size.x;
            m_viewportRect.h = m_size.y * m_aspect;
        }
        m_viewportRect.x = m_size.x / 2.0f - m_viewportRect.w / 2.0f;
        m_viewportRect.y = m_size.y / 2.0f - m_viewportRect.h / 2.0f;
    }

  private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    Viewport m_viewport;
    SDL_FRect m_viewportRect;

    EventHandler m_eventHandler;
    InputHandler m_inputHandler;

    float m_aspect = 1.0f;
    Vec2<unsigned int> m_size;
};
