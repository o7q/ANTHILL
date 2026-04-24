#pragma once

#include "assets/assets.hpp"
#include "backend/window/window.hpp"
#include "math/vec.hpp"
#include "scene/scene.hpp"
#include <memory>

class Game
{
  public:
    Game(Vec2u windowSize, Vec2u viewportSize)
        : m_window("ANTHILL", windowSize, viewportSize)
    {
        start();
    }
    ~Game();
    Game(const Game &other) = delete;
    Game &operator=(const Game &other) = delete;

  private:
    void start();
    void update_loop();
    void init_binds();

  private:
    Assets m_assets;
    Window m_window;
    std::unique_ptr<Scene> m_scene = nullptr;
};
