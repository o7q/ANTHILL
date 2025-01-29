#pragma once

#include <SDL3/SDL.h>

#include "window/window.hpp"

class Game
{
public:
    Game();

private:
    void update();

    Window window;
};