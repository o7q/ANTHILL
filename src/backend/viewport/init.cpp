#include "viewport.hpp"

#include "backend/logger/logger.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <cstddef>

Viewport::Viewport(SDL_Window *window, Vec2u size)
{
    if (!window)
    {
        Logger::fatal("Viewport::Viewport()", "SDL_Window* is null!");
    }

    m_renderer = SDL_CreateRenderer(window, NULL);

    if (!m_renderer)
    {
        Logger::fatal("Viewport::Viewport()", "SDL_Renderer* is null!");
    }

    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB24,
                                  SDL_TEXTUREACCESS_STREAMING, size.x, size.y);

    if (!m_texture)
    {
        Logger::fatal("Viewport::Viewport()", "SDL_Texture* is null!");
    }

    m_pixels = (Uint8 *)malloc(size.x * size.y * 3 * sizeof(Uint8));
    memset(m_pixels, 0, size.x * size.y * 3 * sizeof(Uint8));

    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(m_texture, NULL, m_pixels, size.x * 3);

    reset_update_points();

    m_size = size;
    m_aspectRatio = static_cast<float>(size.x) / size.y;

    Logger::info("Viewport::Viewport()",
                 "Successfully initialized the viewport!");
}

Viewport::~Viewport()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }

    if (m_pixels)
    {
        free(m_pixels);
    }

    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
    }
}
