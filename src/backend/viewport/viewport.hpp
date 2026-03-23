#pragma once

#include "backend/texture/texture.hpp"
#include "math/color.hpp"
#include "math/vec.hpp"
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

    Vec2u getSize() const { return m_size; }
    float getAspectRatio() const { return m_aspectRatio; }

    void recalculatePresentRect(Vec2u windowSize, float windowAspect);

    Vec2i windowToViewportPosition(Vec2f windowPosition);

  public:
    void drawSegment(Vec2i p1, Vec2i p2, Color color);
    void drawRectOutline(Vec2i p1, Vec2i p2, Color color);
    void drawRectFilled(Vec2i p1, Vec2i p2, Color color);
    void drawTexture(const Texture &texture, Vec2i pos);
    void drawTextureRotated(const Texture &texture, Vec2i pos, float angle,
                            std::optional<Vec2i> rotateOrigin = std::nullopt,
                            int overdraw = 1);

  private:
    void update_pixel_changes();
    void reset_update_points();
    unsigned int get_pixel_index(unsigned int x, unsigned int y);

  private:
    Vec2u m_size;

    float m_aspectRatio = 1.0f;

    SDL_Texture *m_texture = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    Uint8 *m_pixels = nullptr;

    Vec2u m_update_pos1;
    Vec2u m_update_pos2;
    SDL_Rect m_update_rect;
    SDL_FRect m_presentRect;
    bool m_pixelChanged = false;
};
