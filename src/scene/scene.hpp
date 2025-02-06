#pragma once

#include "../window/window.hpp"

class Scene
{
public:
    Scene(Window &window) : window(window) {}
    virtual ~Scene() {}
    
    virtual void run() {};

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

private:
    bool m_initialized = false;
};