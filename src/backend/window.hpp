#pragma once

#include "event_handler.hpp"
#include "input_handler.hpp"
#include "time_handler.hpp"
#include "types/vec.hpp"
#include "viewport.hpp"
#include <SDL3/SDL_video.h>

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

    Viewport &getViewport() { return *(m_viewport.get()); }
    EventHandler &getEventHandler() { return m_eventHandler; }
    InputHandler &getInputHandler() { return m_inputHandler; }
    TimeHandler &getTimeHandler() { return m_timeHandler; }

  private:
    SDL_Window *m_window = nullptr;

    std::unique_ptr<Viewport> m_viewport;
    EventHandler m_eventHandler;
    InputHandler m_inputHandler;
    TimeHandler m_timeHandler;

    Vec2<unsigned int> m_size;
    float m_aspectRatio = 1.0f;
};
