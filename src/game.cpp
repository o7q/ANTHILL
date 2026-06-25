#include "game.hpp"

void Game::start()
{
    init_binds();
    m_instance.time().setFramerateTarget(60);

    load_scene(SceneID::Main);

    while (m_instance.isRunning())
    {
        m_instance.frameStart();
        update_loop();
        m_instance.frameEnd();
    }
}

Game::~Game() {}
