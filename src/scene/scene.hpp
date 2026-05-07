#pragma once

#include "assets/assets.hpp"
#include "backend/window/window.hpp"
#include "events/event_pool.hpp"
#include "events/scene/base.hpp"
#include "identifiers/scene.hpp"

class Scene
{
  public:
    struct Result
    {
        SceneIDKey id = "n/a";
        bool load     = false;
    };

  public:
    Scene(Window &window, const Assets &assets) : r_window(window), r_assets(assets) {}
    Scene(const Scene &other)            = delete;
    Scene &operator=(const Scene &other) = delete;
    virtual ~Scene()                     = default;

    Result update();

  protected:
    virtual void onStart() = 0;
    virtual void onTick()  = 0;

  private:
    void handle_events();

  protected:
    Window &r_window;
    const Assets &r_assets;
    EventPool<SceneEvent> m_events;

  private:
    bool m_firstTick = true;
    Result m_result;
};
