#pragma once

#include "backend/input/input_handler.hpp"
#include "backend/sound/sound_handler.hpp"
#include "backend/time/time_handler.hpp"
#include "backend/viewport/viewport.hpp"
#include "math/vec.hpp"
#include <SDL3/SDL_video.h>

class Window
{
  public:
    Window(const std::string &name, Vec2u windowSize, Vec2u viewportSize);
    Window(const Window &other) = delete;
    Window &operator=(const Window &other) = delete;
    ~Window();

    void frameStart();
    void frameEnd();

    void update();
    void clear();
    void present();

    Viewport &getViewport() { return m_viewport; }
    SoundHandler &getSoundHandler() { return m_soundHandler; }
    InputHandler &getInputHandler() { return m_inputHandler; }
    TimeHandler &getTimeHandler() { return m_timeHandler; }

    bool isRunning() const { return m_running; }

  private:
    SDL_Window *m_window = nullptr;

    Viewport m_viewport;
    SoundHandler m_soundHandler;
    InputHandler m_inputHandler;
    TimeHandler m_timeHandler;

    Vec2u m_size;
    float m_aspectRatio = 1.0f;

    bool m_running = true;
};
