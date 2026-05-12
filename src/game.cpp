#include "game.hpp"
#include "scenes/main/main_scene.hpp"

void Game::start()
{
    init_binds();

    m_scene = std::make_unique<MainScene>(m_window, m_assets);

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
