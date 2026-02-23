#pragma once

#include "engine/vec.hpp"
#include "event_handler.hpp"
#include "input_handler.hpp"
#include "time_handler.hpp"
#include "viewport.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <optional>

class Window
{
  public:
    Window(Vec2<unsigned int> windowSize, Vec2<unsigned int> viewportSize);
    Window(const Window &other) = delete;
    Window &operator=(const Window &other) = delete;
    ~Window();

    void frameStart();
    void frameEnd();

    void render();

    Viewport &getViewport() { return m_viewport; }
    EventHandler &getEventHandler() { return m_eventHandler; }
    InputHandler &getInputHandler() { return m_inputHandler; }
    TimeHandler &getTimeHandler() { return m_timeHandler; }

    std::optional<Vec2<unsigned int>>
    windowToViewportPosition(Vec2<float> windowPosition);

  private:
    void recalculate_viewport_rect();

  private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    Viewport m_viewport;
    SDL_FRect m_viewportRect;

    EventHandler m_eventHandler;
    InputHandler m_inputHandler;
    TimeHandler m_timeHandler;

    Vec2<unsigned int> m_size;
    float m_aspectRatio = 1.0f;
};
