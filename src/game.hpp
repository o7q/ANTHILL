#pragma once

#include <SDL3/SDL.h>

#include "window/window.hpp"
#include "scene/common.hpp"
#include "assets/assets.hpp"

class Game
{
public:
    Game();

private:
    void update_scene();
    void create_current_scene();

    Window window;
    Assets assets;

    Scene *scene = nullptr;
    SceneID current_scene = SceneID::Main;
};