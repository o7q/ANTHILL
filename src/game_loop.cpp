#include "game.hpp"

#include "scenes/testing/testing.hpp"
#include <optional>

void Game::update_loop()
{
    if (!currentScene)
    {
        return;
    }

    std::optional<SceneID> resultID = currentScene->update();

    if (!resultID.has_value())
    {
        return;
    }

    SceneID id = resultID.value();

    if (id == m_currentSceneID)
    {
        return;
    }

    switch (id)
    {
    case SceneID::Testing:
        currentScene = std::make_unique<TestScene>(m_window, m_assets);
        break;
    }

    m_currentSceneID = id;
}
