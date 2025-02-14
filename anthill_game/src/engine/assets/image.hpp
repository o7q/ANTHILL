#pragma once

#include <string>

#include <SDL3_image/SDL_image.h>

#include "../logger/logger.hpp"

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

    SDL_Surface *getSDLSurface() const
    {
        return m_surface;
    }

private:
    SDL_Surface *m_surface = nullptr;
};