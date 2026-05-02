#pragma once

#include "assets/assets.hpp"
#include "backend/window/window.hpp"
#include "events/backend/base.hpp"
#include "events/event_pool.hpp"
#include "identifiers/scene.hpp"

class Scene
{
  public:
    Scene(SceneIDKey selfID, Window &window, const Assets &assets)
        : r_window(window), r_assets(assets), m_selfID(selfID), m_sceneSwitchID(selfID)
    {
    }
    Scene(const Scene &other)            = delete;
    Scene &operator=(const Scene &other) = delete;
    virtual ~Scene()                     = default;

    SceneIDKey update();
    SceneIDKey getID() { return m_selfID; }

  protected:
    virtual void onStart() = 0;
    virtual void onTick()  = 0;

    void requestSceneChange(SceneIDKey id) { m_sceneSwitchID = id; }

  private:
    void handleBackendEvents();

  protected:
    Window &r_window;
    const Assets &r_assets;
    EventPool<BackendEvent> m_backendEvents;

  private:
    bool m_firstTick           = true;
    const SceneIDKey m_selfID  = SceneID::None;
    SceneIDKey m_sceneSwitchID = SceneID::None;
};
