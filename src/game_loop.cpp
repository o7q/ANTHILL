#include "game.hpp"

#include "scenes/testing/testing.hpp"
#include "scenes/testing2/testing2.hpp"

void Game::update_loop()
{
    if (!m_scene)
    {
        return;
    }

    m_scene->update();

    Scene::Result result = m_scene->getResult();

    if (!result.shouldLoadScene)
    {
        return;
    }

    switch (result.sceneLoadID)
    {
    case SceneID::Testing:
        m_scene = std::make_unique<TestScene>(m_assets, m_window);
        break;
    case SceneID::Testing2:
        m_scene = std::make_unique<TestScene2>(m_assets, m_window);
        break;
    }
}
