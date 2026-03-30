#include "game.hpp"
#include "scenes/testing/testing.hpp"

void Game::start()
{
    init_binds();
    
    m_scene = std::make_unique<TestScene>(m_assets, m_window);
    
    m_window.getTimeHandler().setMaxFPS(144);
    while (m_window.isRunning())
    {
        m_window.frameStart();
        m_window.getViewport().clear();

        update_loop();

        m_window.render();
        m_window.frameEnd();
    }
}
