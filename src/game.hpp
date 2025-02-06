#pragma once

#include <SDL3/SDL.h>

#include "window/window.hpp"
#include "scene/scene_main.hpp"

class Game
{
public:
    Game();

private:
    void update();

    Window window;
    Scene *scene = nullptr;
};