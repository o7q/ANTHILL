#pragma once

#include "color.hpp"
#include "vec.hpp"
#include <SDL3/SDL_render.h>
#include <limits>

class Viewport
{
  public:
    Viewport() = default;
    Viewport(const Viewport &other) = delete;
    Viewport &operator=(const Viewport &other) = delete;
    ~Viewport()
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

    void init(SDL_Renderer *renderer, Vec2<unsigned int> size)
    {
        m_texture =
            SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_STREAMING, size.x, size.y);

        m_pixels = new Uint32[size.x * size.y];
        for (unsigned int i = 0; i < size.x * size.y; ++i)
        {
            m_pixels[i] = 0x00000000;
        }

        SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
        SDL_UpdateTexture(m_texture, NULL, m_pixels, size.x * sizeof(Uint32));

        reset_update_points();

        m_size = size;
        m_aspectRatio = static_cast<float>(size.x) / size.y;
    }

    void setPixel(Vec2<unsigned int> pos, Color color)
    {
        Uint32 color32 = (static_cast<uint32_t>(color.r) << 24) |
                         (static_cast<uint32_t>(color.g) << 16) |
                         (static_cast<uint32_t>(color.b) << 8) | 0xFF;

        if (pos.x >= m_size.x || pos.y >= m_size.y)
        {
            return;
        }

        const uint32_t index = pos.y * m_size.x + pos.x;

        if (m_pixels[index] == color32)
        {
            return;
        }

        m_pixels[index] = color32;

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

        m_pixel_changed = true;
    }

    Color getPixel(Vec2<unsigned int> pos)
    {
        if (pos.x >= m_size.x || pos.y >= m_size.y)
        {
            return Color();
        }

        const unsigned int index = pos.y * m_size.x + pos.x;

        Uint32 color32 = m_pixels[index];

        return Color(static_cast<uint8_t>((color32 >> 24)),
                     static_cast<uint8_t>((color32 >> 16)),
                     static_cast<uint8_t>((color32 >> 8)));
    }

    Vec2<unsigned int> getSize() const { return m_size; }
    float getAspectRatio() const { return m_aspectRatio; }

    void updateSDLTexture()
    {
        if (!m_pixel_changed)
        {
            return;
        }

        void *update_pixels =
            &m_pixels[m_update_rect.y * m_size.x + m_update_rect.x];
        SDL_UpdateTexture(m_texture, &m_update_rect, update_pixels,
                          m_size.x * sizeof(Uint32));
        reset_update_points();

        m_pixel_changed = false;
    }

    SDL_Texture *getSDLTexture() { return m_texture; }

  private:
    void reset_update_points()
    {
        m_update_pos1.x = std::numeric_limits<unsigned int>::max();
        m_update_pos1.y = std::numeric_limits<unsigned int>::max();
        m_update_pos2.x = 0;
        m_update_pos2.y = 0;
    }

  private:
    Vec2<unsigned int> m_size;

    float m_aspectRatio = 1.0f;

    SDL_Texture *m_texture = nullptr;
    Uint32 *m_pixels = nullptr;

    Vec2<unsigned int> m_update_pos1;
    Vec2<unsigned int> m_update_pos2;
    SDL_Rect m_update_rect;
    bool m_pixel_changed = false;
};
