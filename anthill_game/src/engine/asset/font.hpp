#pragma once

#include <string>

#include <SDL3_ttf/SDL_ttf.h>

#include "../logger/logger.hpp"

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
            Log::log(Log::Level::Error, "AssetLoader/fonts", "Unable to load font \"" + path + '\"');
        }
    }
    ~Font()
    {
        TTF_CloseFont(font);
    }

    TTF_Font *font = nullptr;
};