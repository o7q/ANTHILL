#pragma once

#include "backend/viewport/render_command.hpp"
#include "math/color.hpp"
#include "math/vec.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

class Viewport
{
  public:
    Viewport(SDL_Window *window, Vec2u size);
    Viewport(const Viewport &other) = delete;
    Viewport &operator=(const Viewport &other) = delete;
    ~Viewport();

    void present();
    void clear();

    Vec2u getSize() const { return m_size; }
    float getAspectRatio() const { return m_aspectRatio; }

    void recalculatePresentRect(Vec2u windowSize, float windowAspect);

    Vec2i windowToViewportPosition(Vec2f windowPosition);

    void render(std::vector<RenderCommand>& commands);
    void renderDirect(const RenderCommandData &data);

  private:
    void set_pixel(Vec2u pos, Color color);
    Color get_pixel(Vec2u pos);

    void render_points(const PointsRenderCommandData &data);
    void render_segment(const SegmentRenderCommandData &data);
    void render_rect(const RectangleRenderCommandData &data);
    void render_rect_outline(const RectangleRenderCommandData &data);
    void render_rect_fill(const RectangleRenderCommandData &data);
    void render_texture(const TextureRenderCommandData &data);
    void render_texture_basic(const TextureRenderCommandData &data);
    void render_texture_rotated(const TextureRenderCommandData &data);

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
