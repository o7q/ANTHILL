#pragma once

#include "assets/assets.hpp"
#include "backend/input/input_handler.hpp"
#include "backend/time/time_handler.hpp"
#include "backend/window/window.hpp"
#include "identifiers/scene.hpp"

class Scene
{
  public:
    struct Result
    {
        SceneID sceneLoadID;
        bool shouldLoadScene = false;
    };

  public:
    Scene(Window &window, const Assets &assets)
        : r_window(window), r_viewport(window.getViewport()),
          r_input(window.getInputHandler()), r_time(window.getTimeHandler()),
          r_assets(assets)
    {
    }
    Scene(const Scene &other) = delete;
    Scene &operator=(const Scene &other) = delete;
    virtual ~Scene() = default;

    void update();

    Result getResult() { return m_result; }

  protected:
    virtual void onStart() = 0;
    virtual void onTick() = 0;

    void loadScene(SceneID id)
    {
        m_result.sceneLoadID = id;
        m_result.shouldLoadScene = true;
    }

  protected:
    Window &r_window;
    Viewport &r_viewport;
    InputHandler &r_input;
    TimeHandler &r_time;
    const Assets &r_assets;

  private:
    bool m_firstTick = true;
    Result m_result;
};
