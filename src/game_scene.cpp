#include "game.hpp"

#include "core/logger/logger.hpp"
#include "scenes/level_test/level_test_scene.hpp"
#include "scenes/main/main_scene.hpp"
#include "scenes/verlet_test/verlet_test_scene.hpp"

void Game::load_scene(SceneID id)
{
    switch (id)
    {
    case SceneID::Main:
        m_scene = std::make_unique<MainScene>(m_window, m_assets);
        break;
    case SceneID::VerletTest:
        m_scene = std::make_unique<VerletTestScene>(m_window);
        break;
    case SceneID::LevelTest:
        m_scene = std::make_unique<LevelTestScene>(m_window);
        break;
    default:
        Logger::error("Game::update_loop()", "Recieved unsupported scene change!");
        break;
    }
}
