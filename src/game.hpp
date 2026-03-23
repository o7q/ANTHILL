#pragma once

#include "assets/assets.hpp"
#include "backend/window/window.hpp"
#include "math/vec.hpp"
#include "scene/scene.hpp"
#include "scenes/testing/testing.hpp"
#include <SDL3/SDL_keycode.h>
#include <memory>

class Game
{
  public:
    Game(Vec2u windowSize, Vec2u viewportSize)
        : m_window("ANTHILL", windowSize, viewportSize)
    {
        start();
    }
    Game(const Game &other) = delete;
    Game &operator=(const Game &other) = delete;

  private:
    void start()
    {
        init_binds();

        m_window.getTimeHandler().setTargetFramerate(144);
        // m_window.getTimeHandler().setSpeedMultiplier(0.3f);

        m_scene = std::make_unique<TestScene>(m_assets, m_window);

        while (m_window.isRunning())
        {
            m_window.frameStart();
            m_window.getViewport().clear();

            update_loop();

            m_window.render();
            m_window.frameEnd();
        }
    }

  private:
    void update_loop();
    void init_binds();

  private:
    Assets m_assets;
    Window m_window;
    std::unique_ptr<Scene> m_scene = nullptr;
};
