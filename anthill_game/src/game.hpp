#pragma once

#include <SDL3/SDL.h>

#include "scene/scene_manager.hpp"

#include "engine/window/window.hpp"
#include "assets/assets.hpp"

class Game
{
public:
    Game();

private:
    Window m_window;
    Assets m_assets;

    SceneManager m_scene_manager;
};