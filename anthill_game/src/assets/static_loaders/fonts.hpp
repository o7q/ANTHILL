#pragma once

#include <SDL3_ttf/SDL_ttf.h>

struct Fonts
{
    struct Font
    {
        void create(const std::string &path, int size)
        {
            font = TTF_OpenFont(path.c_str(), size);
        }
        ~Font()
        {
            TTF_CloseFont(font);
        }

        TTF_Font *font = nullptr;
    };

    Fonts()
    {
        alagard.create("assets/fonts/alagard.ttf", 14);
        silkscreen.create("assets/fonts/silkscreen.ttf", 14);
    }

    Font alagard;
    Font silkscreen;
};