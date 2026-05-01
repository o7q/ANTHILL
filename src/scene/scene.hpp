#pragma once

#include "assets/assets.hpp"
#include "backend/input/input_handler.hpp"
#include "backend/sound/sound_handler.hpp"
#include "backend/time/time_handler.hpp"
#include "backend/window/window.hpp"
#include "events/backend/base.hpp"
#include "events/event_pool.hpp"
#include "identifiers/scene.hpp"

class Scene
{
  public:
    struct Result
    {
        SceneIDKey sceneLoadID = SceneID::None;
        bool shouldLoadScene   = false;
    };

  public:
    Scene(const Assets &assets, Window &window) : r_assets(assets), r_window(window) {}
    Scene(const Scene &other)            = delete;
    Scene &operator=(const Scene &other) = delete;
    virtual ~Scene()                     = default;

    void update();

    Result getResult() { return m_result; }

  protected:
    virtual void onStart() = 0;
    virtual void onTick()  = 0;

    void loadScene(SceneIDKey id)
    {
        m_result.sceneLoadID     = id;
        m_result.shouldLoadScene = true;
    }

    EventPool<BackendEvent> m_backendEvents;

  private:
    void handleBackendEvents();

  protected:
    const Assets &r_assets;
    Window &r_window;

  private:
    bool m_firstTick = true;
    Result m_result;
};
