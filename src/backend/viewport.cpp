#include "viewport.hpp"

#include "types/vec.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <cstddef>

Viewport::Viewport(SDL_Window *window, unsigned int width, unsigned int height)
{
    m_renderer = SDL_CreateRenderer(window, NULL);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB24,
                                  SDL_TEXTUREACCESS_STREAMING, width, height);

    m_pixels = new Uint8[width * height * 3];
    memset(m_pixels, 0, width * height * 3 * sizeof(Uint8));

    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(m_texture, NULL, m_pixels, width * 3);

    reset_update_points();

    m_size = Vec2<unsigned int>(width, height);
    m_aspectRatio = static_cast<float>(width) / height;
}

Viewport::~Viewport()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    if (m_pixels)
    {
        delete[] m_pixels;
        m_pixels = nullptr;
    }

    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
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
