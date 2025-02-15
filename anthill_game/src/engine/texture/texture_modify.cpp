#include "texture.hpp"

#include <SDL3/SDL.h>

void Texture::setPixel(int x, int y, Uint32 color)
{
    if (x < 0 || y < 0 || x >= m_size.x || y >= m_size.y)
    {
        return;
    }

    const unsigned int index = y * m_size.x + x;

    if (m_pixels[index] == color)
    {
        return;
    }

    m_pixels[index] = color;

    if (x < m_update_pos1.x)
    {
        m_update_pos1.x = x;
    }
    if (y < m_update_pos1.y)
    {
        m_update_pos1.y = y;
    }
    if (x > m_update_pos2.x)
    {
        m_update_pos2.x = x;
    }
    if (y > m_update_pos2.y)
    {
        m_update_pos2.y = y;
    }

    m_update_rect.x = m_update_pos1.x;
    m_update_rect.y = m_update_pos1.y;
    m_update_rect.w = m_update_pos2.x - m_update_pos1.x + 1;
    m_update_rect.h = m_update_pos2.y - m_update_pos1.y + 1;

    m_pixel_changed = true;
}

void Texture::update()
{
    if (!m_pixel_changed)
    {
        return;
    }

    void *update_pixels = &m_pixels[m_update_rect.y * m_size.x + m_update_rect.x];
    SDL_UpdateTexture(m_texture, &m_update_rect, update_pixels, m_size.x * sizeof(Uint32));
    reset_update_points();

    m_pixel_changed = false;
}