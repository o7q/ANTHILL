#include "game.hpp"

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

    load_scene(result.id.value());
}
