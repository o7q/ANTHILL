#pragma once

#include <SDL3_image/SDL_image.h>
#include "../../logger/logger.hpp"

struct Images
{
    struct Image
    {
        void create(const std::string &path)
        {
            surface = IMG_Load(path.c_str());
            if (surface == NULL)
            {
                Log::log(Log::Type::Error, "AssetLoader/images", "Unable to load image \"" + path + '\"');
            }
        }
        ~Image()
        {
            SDL_DestroySurface(surface);
        }

        SDL_Surface *surface = nullptr;
    };

    Images()
    {
        crosshair.create("assets/images/gui/crosshair.png");
    }

    Image crosshair;
};