#pragma once

#include <SDL3_ttf/SDL_ttf.h>

struct Fonts
{
    struct Font
    {
        void create(const std::string &path, int size)
        {
            if (font != nullptr)
            {
                TTF_CloseFont(font);
            }

            font = TTF_OpenFont(path.c_str(), size);
            if (font == NULL)
            {
                Log::log(Log::Type::Error, "AssetLoader/fonts", "Unable to load font \"" + path + '\"');
            }
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