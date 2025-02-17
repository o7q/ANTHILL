#pragma once

#include <string>
#include <SDL3_ttf/SDL_ttf.h>

#include "../../engine/logger/logger.hpp"

struct Fonts
{
    Fonts()
    {
        load_font(alagard, "assets/fonts/alagard.ttf", 14);
        load_font(silkscreen, "assets/fonts/silkscreen.ttf", 14);
    }

    ~Fonts()
    {
        destroy_font(alagard);
        destroy_font(silkscreen);
    }

    TTF_Font *alagard = nullptr;
    TTF_Font *silkscreen = nullptr;

private:
    void load_font(TTF_Font *&font, const std::string &path, int size)
    {
        if (font != nullptr)
        {
            TTF_CloseFont(font);
        }

        font = TTF_OpenFont(path.c_str(), size);
        if (font == NULL)
        {
            Log::log(Log::Level::Error, "Assets/fonts", "Unable to load font \"" + path + '\"');
        }
    }

    void destroy_font(TTF_Font *font)
    {
        if (font != nullptr)
        {
            TTF_CloseFont(font);
            font = nullptr;
        }
    }
};