#include "viewport.hpp"

void Viewport::present()
{
    update_pixel_changes();
    SDL_RenderTexture(m_renderer, m_texture, NULL, &m_presentRect);
    SDL_RenderPresent(m_renderer);
}

void Viewport::clear()
{
    SDL_RenderClear(m_renderer);

    memset(m_pixels, 0, m_size.x * m_size.y * 3 * sizeof(Uint8));
    SDL_UpdateTexture(m_texture, NULL, m_pixels, m_size.x * 3);
}
