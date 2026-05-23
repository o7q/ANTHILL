#include "game.hpp"

void Game::start()
{
    init_binds();

    load_scene(SceneID::Main);
    m_window.getTime().setMaxFPS(60);
    while (m_window.isRunning())
    {
        m_window.frameStart();
        update_loop();
        m_window.frameEnd();
    }
}

Game::~Game() {}
