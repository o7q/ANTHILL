#pragma once

#include "types/color.hpp"
#include "types/vec.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

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
