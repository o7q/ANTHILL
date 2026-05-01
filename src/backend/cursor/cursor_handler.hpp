#pragma once

#include "backend/texture/texture.hpp"
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_surface.h>
#include <cstring>

// TODO
class CursorHandler
{
  public:
    CursorHandler() {}
    ~CursorHandler() { destroy(); }

    void switchCursor(const Texture &texture)
    {
        destroy();

        std::memcpy(m_pixelData, texture.getPixels().data(), texture.getSize().x * texture.getSize().y * 4);

        m_surface = SDL_CreateSurfaceFrom(texture.getSize().x, texture.getSize().y, SDL_PIXELFORMAT_RGBA32,
                                          m_pixelData, texture.getSize().x * 4);

        m_cursor = SDL_CreateColorCursor(m_surface, 0, 0);

        SDL_SetCursor(m_cursor);
    }

  private:
    void destroy()
    {
        if (m_cursor)
        {
            SDL_DestroyCursor(m_cursor);
        }
        if (m_surface)
        {
            SDL_DestroySurface(m_surface);
        }
        if (m_pixelData)
        {
            delete[] m_pixelData;
        }
    }

  private:
    SDL_Cursor *m_cursor   = nullptr;
    SDL_Surface *m_surface = nullptr;
    Uint8 *m_pixelData     = nullptr;
};
