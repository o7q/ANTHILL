#pragma once

#include <string>
#include <SDL3_image/SDL_image.h>

#include "../../engine/logger/logger.hpp"

struct Surfaces
{
    Surfaces()
    {
        load_surface(crosshair_1x, "assets/images/crosshair/crosshair_1x.png");
        load_surface(crosshair_2x, "assets/images/crosshair/crosshair_2x.png");
    }

    ~Surfaces()
    {
        destroy_surface(crosshair_1x);
        destroy_surface(crosshair_2x);
    }

    SDL_Surface *crosshair_1x = nullptr;
    SDL_Surface *crosshair_2x = nullptr;

private:
    void load_surface(SDL_Surface *&surface, const std::string &path)
    {
        if (surface != nullptr)
        {
            SDL_DestroySurface(surface);
            surface = nullptr;
        }

        surface = IMG_Load(path.c_str());
        if (surface == NULL)
        {
            Log::log(Log::Level::Error, "Assets/surfaces", "Unable to load image \"" + path + '\"');
            surface = SDL_CreateSurface(1, 1, SDL_PIXELFORMAT_RGBA8888);
        }
    }

    void destroy_surface(SDL_Surface *surface)
    {
        if (surface != nullptr)
        {
            SDL_DestroySurface(surface);
            surface = nullptr;
        }
    }
};