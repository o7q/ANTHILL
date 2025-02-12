#pragma once

#include <SDL3_image/SDL_image.h>
#include "../../logger/logger.hpp"

struct Image
{
    void create(const std::string &path)
    {
        if (m_surface != nullptr)
        {
            SDL_DestroySurface(m_surface);
        }

        m_surface = IMG_Load(path.c_str());
        if (m_surface == NULL)
        {
            Log::log(Log::Type::Error, "AssetLoader/images", "Unable to load image \"" + path + '\"');
        }
    }
    ~Image()
    {
        SDL_DestroySurface(m_surface);
    }

    SDL_Surface* getSDLSurface() const
    {
        return m_surface;
    }

private:
    SDL_Surface *m_surface = nullptr;
};

struct Images
{
    Images()
    {
        crosshair_1x.create("assets/images/crosshair/crosshair_1x.png");
        crosshair_2x.create("assets/images/crosshair/crosshair_2x.png");
    }

    Image crosshair_1x;
    Image crosshair_2x;
};