#pragma once

#include "texture.hpp"
#include "types/color.hpp"
#include "types/vec.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <optional>

class Viewport
{
  public:
    Viewport(SDL_Window *window, unsigned int width, unsigned int height);
    Viewport(const Viewport &other) = delete;
    Viewport &operator=(const Viewport &other) = delete;
    ~Viewport();

    void render();
    void clear();

    void setPixel(unsigned int x, unsigned int y, Color color);
    Color getPixel(unsigned int x, unsigned int y);

    void drawTexture(const Texture &texture, unsigned int x = 0,
                     unsigned int y = 0);

    void drawSegment(Vec2<int> p1, Vec2<int> p2, Color color);

    void drawRectOutline(Vec2<int> p1, Vec2<int> p2, Color color)
    {
        // top
        for (int x = p1.x; x <= p2.x; ++x)
        {
            setPixel(x, p1.y, color);
        }

        // left
        for (int y = p1.y + 1; y < p2.y; ++y)
        {
            setPixel(p1.x, y, color);
        }

        // right
        for (int y = p1.y + 1; y < p2.y; ++y)
        {
            setPixel(p2.x, y, color);
        }

        // bottom
        for (int x = p1.x; x <= p2.x; ++x)
        {
            setPixel(x, p2.y, color);
        }
    }

    void drawRectFilled(Vec2<int> p1, Vec2<int> p2, Color color)
    {
        for (int y = p1.y; y <= p2.y; ++y)
        {
            for (int x = p1.x; x <= p2.x; ++x)
            {
                setPixel(x, y, color);
            }
        }
    }

    Vec2<unsigned int> getSize() const { return m_size; }
    float getAspectRatio() const { return m_aspectRatio; }

    void recalculatePresentRect(Vec2<unsigned int> windowSize,
                                float windowAspect);

    Vec2<int> windowToViewportPosition(Vec2<float> windowPosition);

  private:
    void update_pixel_changes();
    void reset_update_points();
    unsigned int get_pixel_index(unsigned int x, unsigned int y);

  private:
    Vec2<unsigned int> m_size;

    float m_aspectRatio = 1.0f;

    SDL_Texture *m_texture = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    Uint8 *m_pixels = nullptr;

    Vec2<unsigned int> m_update_pos1;
    Vec2<unsigned int> m_update_pos2;
    SDL_Rect m_update_rect;
    SDL_FRect m_presentRect;
    bool m_pixelChanged = false;
};
