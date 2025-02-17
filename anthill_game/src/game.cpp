#include "game.hpp"

#include "engine/math/random.hpp"

Game::Game() : m_window("ANTHILL", 512, 512, 360), m_scene_manager(m_window, m_assets)
{
    m_assets.load();
    m_window.time().setTargetFramerate(144);

    while (m_window.isOpen())
    {
        m_window.start();

        m_scene_manager.update();

        m_window.end();
    }

    m_assets.destroy();
}