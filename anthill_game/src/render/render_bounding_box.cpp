#include "render_manager.hpp"

void RenderManager::debug_renderBoundingBox(const BoundingBox &boundingBox, Color color, const Camera *camera)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

    Vec2<float> top_left = boundingBox.getP1();
    Vec2<float> size = boundingBox.getSize();

    SDL_FRect rect;
    rect.x = top_left.x;
    rect.y = top_left.y;
    rect.w = size.x;
    rect.h = size.y;

    if (camera != nullptr)
    {
        Vec2<float> cam_pos = camera->getPosition() - Vec2<float>(m_scale, m_scale) / 2.0f;
        rect.x -= cam_pos.x;
        rect.y -= cam_pos.y;
    }

    rect.x = static_cast<int>(rect.x);
    rect.y = static_cast<int>(rect.y);
    rect.w = static_cast<int>(rect.w);
    rect.h = static_cast<int>(rect.h);

    SDL_RenderRect(m_renderer, &rect);

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
}