#pragma once

#include "backend/input/input_handler.hpp"
#include "backend/time/time_handler.hpp"
#include "backend/window/window.hpp"
#include <optional>

enum class SceneID
{
    Testing
};

class Scene
{
  public:
    Scene(Window &window)
        : r_window(window), r_viewport(window.getViewport()),
          r_input(window.getInputHandler()), r_time(window.getTimeHandler())
    {
    }
    Scene(const Scene &other) = delete;
    Scene &operator=(const Scene &other) = delete;
    virtual ~Scene() {}

    virtual std::optional<SceneID> update() { return std::nullopt; }

  protected:
    bool start();
    bool tick();

  protected:
    Window &r_window;
    Viewport &r_viewport;
    InputHandler &r_input;
    TimeHandler &r_time;

  private:
    bool m_firstTick = true;
    std::optional<SceneID> m_selfID;
};
