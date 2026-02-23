#pragma once

#include "engine/backend/window.hpp"
#include <optional>

enum class SceneID
{
    Testing
};

class Scene
{
  public:
    Scene(Window &window) : r_window(window) {}
    Scene(const Scene &other) = delete;
    Scene &operator=(const Scene &other) = delete;
    virtual ~Scene() {}

    virtual std::optional<SceneID> update() { return std::nullopt; }

  protected:
    bool start()
    {
        if (m_firstTick)
        {
            m_firstTick = false;
            return true;
        }

        return false;
    }
    bool tick() { return true; }

  protected:
    Window &r_window;

  private:
    bool m_firstTick = true;
    std::optional<SceneID> m_selfID;
};
