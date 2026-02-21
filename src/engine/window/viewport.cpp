#include "viewport.hpp"

#include "engine/color.hpp"
#include "engine/vec.hpp"
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

void Viewport::init(SDL_Renderer *renderer, unsigned int width,
                    unsigned int height)
{
    m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24,
                                  SDL_TEXTUREACCESS_STREAMING, width, height);

    m_pixels = new Uint8[width * height * 3];
    memset(m_pixels, 0, width * height * 3 * sizeof(Uint8));

    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(m_texture, NULL, m_pixels, width * 3);

    reset_update_points();

    m_size = Vec2<unsigned int>(width, height);
    m_aspectRatio = static_cast<float>(width) / height;
}

void Viewport::setPixel(unsigned int x, unsigned int y, Color color)
{
    if (x >= m_size.x || y >= m_size.y)
    {
        return;
    }

    const unsigned int index = get_pixel_index(x, y);

    m_pixels[index] = color.r;
    m_pixels[index + 1] = color.g;
    m_pixels[index + 2] = color.b;

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

    m_pixelChanged = true;
}

Color Viewport::getPixel(unsigned int x, unsigned int y)
{
    if (x >= m_size.x || y >= m_size.y)
    {
        return Color();
    }

    const unsigned int index = get_pixel_index(x, y);
    return Color(m_pixels[index], m_pixels[index + 1], m_pixels[index + 2]);
}

void Viewport::renderTexture(const Texture &texture, unsigned int x,
                             unsigned int y)
{
    Vec2<unsigned int> textureSize = texture.getSize();
    Vec2<unsigned int> textureSizeHalf = texture.getSize() / 2;
    for (unsigned int ty = 0; ty < textureSize.y; ++ty)
    {
        for (unsigned int tx = 0; tx < textureSize.x; ++tx)
        {
            Color color = texture.getPixel(tx, ty);
            setPixel(tx + x - textureSizeHalf.x, ty + y - textureSizeHalf.y,
                     color);
        }
    }
}

void Viewport::clear()
{
    memset(m_pixels, 0, m_size.x * m_size.y * 3 * sizeof(Uint8));
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
