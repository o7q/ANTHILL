#pragma once

#include "assets/assets.hpp"
#include "px/basic_types/vec.hpp"
#include "px/instance/instance.hpp"
#include "scene/scene.hpp"
#include <memory>

class Game
{
  public:
    Game(px::Vec2u windowSize, px::Vec2u viewportSize) : m_instance("ANTHILL", windowSize, viewportSize)
    {
        start();
    }
    ~Game();
    Game(const Game &other)            = delete;
    Game &operator=(const Game &other) = delete;

  private:
    void start();
    void update_loop();

    void init_binds();

    void load_scene(SceneID id);

  private:
    Assets m_assets;
    px::Instance m_instance;
    std::unique_ptr<Scene> m_scene = nullptr;
};
