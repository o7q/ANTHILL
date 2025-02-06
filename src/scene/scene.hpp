#pragma once

#include "../window/window.hpp"
#include "../assets/assets.hpp"

enum class SceneID
{
    Main
};

class Scene
{
public:
    Scene(Window &window, Assets &assets) : window(window), assets(assets) {}
    virtual ~Scene() {}

    virtual SceneID run() { return SceneID::Main; }

protected:
    bool init()
    {
        if (m_initialized)
            return false;

        m_initialized = true;
        return true;
    }

    bool update() { return true; }

protected:
    Window &window;
    Assets &assets;

private:
    bool m_initialized = false;
};