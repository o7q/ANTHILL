#include "game.hpp"

void Game::start()
{
    init_binds();

    load_scene(SceneID::DungeonTest);

    m_window.getTime().setMaxFPS(60);
    while (m_window.isRunning())
    {
        m_window.frameStart();
        m_window.update();
        m_window.clear();

        update_loop();

        m_window.present();
        m_window.frameEnd();
    }
}

Game::~Game() {}
