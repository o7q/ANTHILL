#pragma once

#include <SDL3_ttf/SDL_ttf.h>

struct Fonts
{
    Fonts()
    {
        alagard_font = TTF_OpenFont("assets/fonts/alagard.ttf", 12);
    }
    ~Fonts()
    {
        TTF_CloseFont(alagard_font);
    }

    TTF_Font *alagard_font = nullptr;
};