#include "game.hpp"

#include "core/logger/logger.hpp"

#include "scenes/dungeon_test/dungeon_test_scene.hpp"
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
        m_scene = std::make_unique<VerletTestScene>(m_window, m_assets);
        break;
    case SceneID::DungeonTest:
        m_scene = std::make_unique<DungeonTestScene>(m_window, m_assets);
        break;
    default:
        Logger::error("Game::update_loop()", "Recieved unsupported scene change!");
        break;
    }
}
