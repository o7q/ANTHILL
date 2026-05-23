#include "game.hpp"

void Game::start()
{
    init_binds();
    m_window.getTime().setMaxFPS(60);

    load_scene(SceneID::Main);

    while (m_window.isRunning())
    {
        m_window.frameStart();
        update_loop();
        m_window.frameEnd();
    }
}

Game::~Game() {}
