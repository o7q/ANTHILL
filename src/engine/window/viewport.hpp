#pragma once

#include "engine/color.hpp"
#include "engine/texture.hpp"
#include "engine/vec.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

class Viewport
{
  public:
    Viewport() = default;
    Viewport(const Viewport &other) = delete;
    Viewport &operator=(const Viewport &other) = delete;
    ~Viewport();

    void init(SDL_Renderer *renderer, unsigned int width, unsigned int height);

    void setPixel(unsigned int x, unsigned int y, Color color);
    Color getPixel(unsigned int x, unsigned int y);

    void renderTexture(const Texture &texture, unsigned int x = 0,
                       unsigned int y = 0);

    void clear();
    void updatePixelChanges();

    Vec2<unsigned int> getSize() const { return m_size; }
    float getAspectRatio() const { return m_aspectRatio; }
    SDL_Texture *getSDLTexture() { return m_texture; }

  private:
    void reset_update_points();
    unsigned int get_pixel_index(unsigned int x, unsigned int y);

  private:
    Vec2<unsigned int> m_size;

    float m_aspectRatio = 1.0f;

    SDL_Texture *m_texture = nullptr;
    Uint8 *m_pixels = nullptr;

    Vec2<unsigned int> m_update_pos1;
    Vec2<unsigned int> m_update_pos2;
    SDL_Rect m_update_rect;
    bool m_pixelChanged = false;
};
