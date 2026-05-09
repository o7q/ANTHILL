#pragma once

#include "assets/assets.hpp"
#include "backend/window/window.hpp"
#include "events/event_pool.hpp"
#include "events/external/base.hpp"
#include "identifiers/scene.hpp"
#include <optional>

class Scene
{
  public:
    struct Result
    {
        std::optional<SceneID> id;
        bool load = false;
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
    EventPool<ExternalEvent> m_events;

  private:
    bool m_firstTick = true;
    Result m_result;
};
