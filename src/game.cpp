#include "game.hpp"
#include "scenes/testing2/testing2.hpp"

void Game::start()
{
    init_binds();

    m_window.getTimeHandler().setTargetFramerate(144);
    // m_window.getTimeHandler().setSpeedMultiplier(0.3f);

    m_scene = std::make_unique<TestScene2>(m_assets, m_window);

    while (m_window.isRunning())
    {
        m_window.frameStart();
        m_window.getViewport().clear();

        update_loop();

        m_window.render();
        m_window.frameEnd();
    }
}
