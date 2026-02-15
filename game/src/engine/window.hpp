#pragma once

#include "event_handler.hpp"
#include "input_hander.hpp"
#include "vec.hpp"
#include "viewport.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>
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

        // m_viewport.init(m_renderer, Vec2<uint16_t>(100, 100));
    }
    ~Window()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    void update()
    {
        m_eventHandler.begin();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            m_eventHandler.poll(event);
            m_inputHandler.poll(event);
        }

        m_inputHandler.update();

        SDL_RenderClear(m_renderer);

        // m_viewport.updateSDLTexture();
        // SDL_RenderTexture(m_renderer, m_viewport.getSDLTexture(), NULL,
        // NULL);

        SDL_RenderPresent(m_renderer);

        SDL_Delay(100);
    }

    EventHandler &getEventHandler() { return m_eventHandler; }
    InputHandler &getInputHandler() { return m_inputHandler; }

  private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    Viewport m_viewport;

    EventHandler m_eventHandler;
    InputHandler m_inputHandler;
};
