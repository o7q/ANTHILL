#pragma once

#include "core/window/window.hpp"
#include "identifiers/scene.hpp"
#include <optional>

class Scene
{
  public:
    Scene(Window &window) : r_window(window) {}
    Scene(const Scene &other)            = delete;
    Scene &operator=(const Scene &other) = delete;
    virtual ~Scene()                     = default;

    std::optional<SceneID> update();

  protected:
    virtual void onStart() = 0;
    virtual void onTick()  = 0;

    void changeScene(SceneID id) { m_result = id; }

  protected:
    Window &r_window;

  private:
    bool m_firstTick = true;
    std::optional<SceneID> m_result;
};
