#include "scene.hpp"

std::optional<SceneID> Scene::update()
{
    m_result = std::nullopt;

    if (m_firstTick)
    {
        onStart();
        m_firstTick = false;
    }

    onTick();

    return m_result;
}
