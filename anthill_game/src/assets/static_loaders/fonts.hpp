#pragma once

#include <SDL3_ttf/SDL_ttf.h>

#include "../../engine/assets/font.hpp"

struct Fonts
{
    Fonts()
    {
        alagard.create("assets/fonts/alagard.ttf", 14);
        silkscreen.create("assets/fonts/silkscreen.ttf", 14);
    }

    Font alagard;
    Font silkscreen;
};