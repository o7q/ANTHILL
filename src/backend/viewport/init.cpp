#include "viewport.hpp"

#include "backend/logger/logger.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <cstddef>

Viewport::Viewport(SDL_Window *window, unsigned int width, unsigned int height)
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
                                  SDL_TEXTUREACCESS_STREAMING, width, height);

    if (!m_texture)
    {
        Logger::fatal("Viewport::Viewport()", "SDL_Texture* is null!");
    }

    m_pixels = (Uint8 *)malloc(width * height * 3 * sizeof(Uint8));
    memset(m_pixels, 0, width * height * 3 * sizeof(Uint8));

    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(m_texture, NULL, m_pixels, width * 3);

    reset_update_points();

    m_size = Vec2u(width, height);
    m_aspectRatio = static_cast<float>(width) / height;

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

void Viewport::render()
{
    SDL_RenderClear(m_renderer);

    update_pixel_changes();
    SDL_RenderTexture(m_renderer, m_texture, NULL, &m_presentRect);

    SDL_RenderPresent(m_renderer);
}

void Viewport::clear()
{
    memset(m_pixels, 0, m_size.x * m_size.y * 3 * sizeof(Uint8));
    SDL_UpdateTexture(m_texture, NULL, m_pixels, m_size.x * 3);
}
