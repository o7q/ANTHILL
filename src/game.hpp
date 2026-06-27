#pragma once

#include "assets/assets.hpp"
#include "px/instance/instance.hpp"
#include "scene/scene.hpp"
#include <memory>

class Game
{
  public:
    Game() : m_instance("ANTHILL", {1280, 720}) { start(); }
    ~Game();
    Game(const Game &other)            = delete;
    Game &operator=(const Game &other) = delete;

  private:
    void start();
    void update_loop();

    void init_binds();

    void load_scene(SceneID id);

  private:
    px::Instance m_instance;
    Assets m_assets;
    std::unique_ptr<Scene> m_scene = nullptr;
};
