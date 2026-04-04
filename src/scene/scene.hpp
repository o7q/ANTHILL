#pragma once

#include "assets/assets.hpp"
#include "backend/input/input_handler.hpp"
#include "backend/sound/sound_handler.hpp"
#include "backend/time/time_handler.hpp"
#include "backend/viewport/render_command.hpp"
#include "backend/window/window.hpp"
#include "events/backend/base.hpp"
#include "events/event_pool.hpp"
#include "scene_ids.hpp"
#include <vector>

class Scene
{
  public:
    struct Result
    {
        SceneID sceneLoadID = SceneID::None;
        bool shouldLoadScene = false;
    };

  public:
    Scene(const Assets &assets, Window &window)
        : r_assets(assets), r_window(window), r_viewport(window.getViewport()),
          r_sound(window.getSoundHandler()), r_input(window.getInputHandler()),
          r_time(window.getTimeHandler())
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
    const Assets &r_assets;
    Window &r_window;
    Viewport &r_viewport;
    SoundHandler &r_sound;
    InputHandler &r_input;
    TimeHandler &r_time;

    EventPool<BackendEvent> m_backendEvents;
    std::vector<RenderCommand> m_renderCommands;

  private:
    bool m_firstTick = true;
    Result m_result;
};
