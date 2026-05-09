#include "game.hpp"

#include "backend/logger/logger.hpp"
#include "identifiers/scene.hpp"
#include "scenes/main/main_scene.hpp"
#include "scenes/test/test_scene.hpp"

void Game::update_loop()
{
    if (!m_scene)
    {
        return;
    }

    Scene::Result result = m_scene->update();

    if (!result.load || !result.id.has_value())
    {
        return;
    }

    switch (result.id.value())
    {
    case SceneID::Main:
        m_scene = std::make_unique<MainScene>(m_window, m_assets);
        break;
    case SceneID::Test:
        m_scene = std::make_unique<TestScene>(m_window, m_assets);
        break;
    default:
        Logger::error("Game::update_loop()", "Recieved unsupported scene change!");
        break;
    }
}
