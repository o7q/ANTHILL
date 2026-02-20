#include "viewport.hpp"

#include "color.hpp"
#include "vec.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <cstddef>
#include <limits>

Viewport::~Viewport()
{
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
    if (m_pixels != nullptr)
    {
        delete[] m_pixels;
        m_pixels = nullptr;
    }
}

void Viewport::init(SDL_Renderer *renderer, Vec2<unsigned int> size)
{
    m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24,
                                  SDL_TEXTUREACCESS_STREAMING, size.x, size.y);

    m_pixels = new Uint8[size.x * size.y * 3];
    memset(m_pixels, 0, size.x * size.y * 3 * sizeof(Uint8));

    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(m_texture, NULL, m_pixels, size.x * 3);

    reset_update_points();

    m_size = size;
    m_aspectRatio = static_cast<float>(size.x) / size.y;
}

void Viewport::setPixel(Vec2<unsigned int> pos, Color color)
{
    if (pos.x >= m_size.x || pos.y >= m_size.y)
    {
        return;
    }

    const unsigned int index = get_pixel_index(pos.x, pos.y);

    m_pixels[index] = color.r;
    m_pixels[index + 1] = color.g;
    m_pixels[index + 2] = color.b;

    if (pos.x < m_update_pos1.x)
    {
        m_update_pos1.x = pos.x;
    }
    if (pos.y < m_update_pos1.y)
    {
        m_update_pos1.y = pos.y;
    }
    if (pos.x > m_update_pos2.x)
    {
        m_update_pos2.x = pos.x;
    }
    if (pos.y > m_update_pos2.y)
    {
        m_update_pos2.y = pos.y;
    }

    m_update_rect.x = m_update_pos1.x;
    m_update_rect.y = m_update_pos1.y;
    m_update_rect.w = m_update_pos2.x - m_update_pos1.x + 1;
    m_update_rect.h = m_update_pos2.y - m_update_pos1.y + 1;

    m_pixelChanged = true;
}

Color Viewport::getPixel(Vec2<unsigned int> pos)
{
    if (pos.x >= m_size.x || pos.y >= m_size.y)
    {
        return Color();
    }

    const unsigned int index = get_pixel_index(pos.x, pos.y);
    return Color(m_pixels[index], m_pixels[index + 1], m_pixels[index + 2]);
}

void Viewport::clear()
{
    memset(m_pixels, 255, m_size.x * m_size.y * 3 * sizeof(Uint8));
    SDL_UpdateTexture(m_texture, NULL, m_pixels, m_size.x * 3);
}

void Viewport::updatePixelChanges()
{
    if (!m_pixelChanged)
    {
        return;
    }

    const unsigned int index =
        get_pixel_index(m_update_rect.x, m_update_rect.y);

    SDL_UpdateTexture(m_texture, &m_update_rect, &m_pixels[index],
                      m_size.x * 3);
    reset_update_points();

    m_pixelChanged = false;
}

void Viewport::reset_update_points()
{
    m_update_pos1.x = std::numeric_limits<unsigned int>::max();
    m_update_pos1.y = std::numeric_limits<unsigned int>::max();
    m_update_pos2.x = 0u;
    m_update_pos2.y = 0u;
}

unsigned int Viewport::get_pixel_index(unsigned int x, unsigned int y)
{
    return (y * m_size.x + x) * 3u;
}
