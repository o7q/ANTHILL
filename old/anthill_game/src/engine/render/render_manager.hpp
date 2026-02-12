#pragma once

#include <string>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "../math/color.hpp"
#include "../math/segment.hpp"
#include "../math/bounding_box.hpp"
#include "../texture/texture.hpp"
#include "../camera/camera.hpp"

class RenderManager
{
public:
    RenderManager() = default;

    void setRenderer(SDL_Renderer *renderer) { m_renderer = renderer; }
    void setScale(Vec2<unsigned int> scaled_size) { m_scaled_size = scaled_size; }

    void renderTexture(const Texture *texture, const Camera *camera = nullptr);
    void renderText(TTF_Font *font, const std::string &text, Vec2<int> position, Color color, Camera *camera = nullptr);

    void debug_renderSegment(const Segment &segment, Color color, const Camera *camera = nullptr);
    void debug_renderPoint(int x, int y, Color color, const Camera *camera = nullptr);
    void debug_renderBoundingBox(const BoundingBox &boundingBox, Color color, const Camera *camera = nullptr);

private:
    SDL_Renderer *m_renderer = nullptr;
    Vec2<unsigned int> m_scaled_size;
};