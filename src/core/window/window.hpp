#pragma once

#include "core/input/input_handler.hpp"
#include "core/math/vec.hpp"
#include "core/sound/sound_handler.hpp"
#include "core/time/time_handler.hpp"
#include "core/viewport/viewport.hpp"
#include <SDL3/SDL_video.h>

class Window
{
  public:
    Window(const std::string &name, Vec2u windowSize, Vec2u viewportSize);
    Window(const Window &other)            = delete;
    Window &operator=(const Window &other) = delete;
    ~Window();

    void frameStart();
    void frameEnd();

    void update();
    void clear();
    void present();

    Viewport &getViewport() { return m_viewport; }
    SoundHandler &getSound() { return m_sound; }
    InputHandler &getInput() { return m_input; }
    TimeHandler &getTime() { return m_time; }

    bool isRunning() const { return m_running; }

  private:
    SDL_Window *m_window = nullptr;

    Viewport m_viewport;
    SoundHandler m_sound;
    InputHandler m_input;
    TimeHandler m_time;

    Vec2u m_size;
    float m_aspectRatio = 1.0f;

    bool m_running = true;
};
