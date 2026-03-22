#include "scene.hpp"

void Scene::update()
{
    if (m_firstTick)
    {
        onStart();
        m_firstTick = false;
    }

    onTick();
}
