#pragma once

#include "scene_id.hpp"

#include "../engine/window/window.hpp"
#include "../assets/assets.hpp"

class Scene
{
public:
    Scene(Window &window, Assets &assets) : m_window(window), m_assets(assets) {}
    virtual ~Scene() {}

    virtual SceneID run() { return SceneID::Main; }
    bool shouldReset() { return m_should_reset; }

protected:
    bool init()
    {
        if (m_initialized)
            return false;

        m_initialized = true;
        return true;
    }

    bool update()
    {
        DT = m_window.time().getDeltaTime();
        FPS = m_window.time().getFramerate();
        return true;
    }
    void reset() { m_should_reset = true; }

protected:
    Window &m_window;
    Assets &m_assets;

protected:
    float DT = 0.0f;
    float FPS = 0.0f;

private:
    bool m_initialized = false;
    bool m_should_reset = false;
};