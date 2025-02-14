#include "scene_manager.hpp"

#include "../engine/window/window.hpp"

#include "../assets/assets.hpp"
#include "../scene_main/scene_main.hpp"

void SceneManager::update()
{
    if (m_scene != nullptr)
    {
        SceneID scene_result = m_scene->run();

        if (scene_result != m_current_scene || m_scene->shouldReset())
        {
            delete m_scene;
            m_scene = nullptr;
            create_scene(scene_result);

            m_current_scene = scene_result;
        }
    }
    else
    {
        create_scene(m_current_scene);
    }
}
void SceneManager::create_scene(SceneID scene_id)
{
    switch (scene_id)
    {
    case SceneID::Main:
        m_scene = new MainScene(m_window, m_assets);
        break;
    }
}