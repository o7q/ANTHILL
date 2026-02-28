#include "scene.hpp"

bool Scene::start()
{
    if (m_firstTick)
    {
        m_firstTick = false;
        return true;
    }

    return false;
}
bool Scene::tick() { return true; }
