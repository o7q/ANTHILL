#include "game.hpp"
#include "scenes/testing/testing.hpp"
#include "scenes/testing2/testing2.hpp"

void Game::start()
{
    init_binds();

    m_scene = std::make_unique<TestScene>(m_assets, m_window);

    m_window.getTimeHandler().setMaxFPS(144);
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
