#pragma once

#include "identifiers/scene.hpp"
#include "px/instance/instance.hpp"
#include <optional>

class Scene
{
  public:
    Scene(px::Instance &instance) : r_instance(instance) {}
    Scene(const Scene &other)            = delete;
    Scene &operator=(const Scene &other) = delete;
    virtual ~Scene()                     = default;

    std::optional<SceneID> update();

  protected:
    virtual void onStart() = 0;
    virtual void onTick()  = 0;

    void changeScene(SceneID id) { m_result = id; }

  protected:
    px::Instance &r_instance;

  private:
    bool m_firstTick = true;
    std::optional<SceneID> m_result;
};
