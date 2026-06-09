#include "game.hpp"
#include "identifiers/scene.hpp"
#include <optional>

void Game::update_loop()
{
    if (!m_scene)
    {
        return;
    }

    std::optional<SceneID> result = m_scene->update();

    if (!result.has_value())
    {
        return;
    }

    load_scene(result.value());
}
