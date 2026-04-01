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
    struct TextureRotateSettings
    {
        float angle = 0.0f;
        std::optional<Vec2i> origin;
        int overdraw = 1;
    };

    struct TextureDrawSettings
    {
        Vec2i pos;
        bool flipX = false;
        bool flipY = false;
        std::optional<TextureRotateSettings> rotateSettings;
    };

  public:
    Viewport(SDL_Window *window, Vec2u size);
    Viewport(const Viewport &other) = delete;
    Viewport &operator=(const Viewport &other) = delete;
    ~Viewport();

    void render();
    void clear();

    void setPixel(Vec2u pos, Color color);
    Color getPixel(Vec2u pos);

    Vec2u getSize() const { return m_size; }
    float getAspectRatio() const { return m_aspectRatio; }

    void recalculatePresentRect(Vec2u windowSize, float windowAspect);

    Vec2i windowToViewportPosition(Vec2f windowPosition);

  public:
    void drawSegment(Vec2i p1, Vec2i p2, Color color);
    void drawRectOutline(Vec2i p1, Vec2i p2, Color color);
    void drawRectFilled(Vec2i p1, Vec2i p2, Color color);
    void drawTexture(const Texture &texture, TextureDrawSettings settings);

  private:
    void draw_texture_rotated(const Texture &texture,
                              TextureDrawSettings settings);

  private:
    void update_pixel_changes();
    void reset_update_points();
    unsigned int get_pixel_index(Vec2u pos);

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
