#include "render_manager.hpp"

void RenderManager::debug_renderSegment(const Segment &segment, Color color, const Camera *camera)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

    Segment seg = segment;

    if (camera != nullptr)
    {
        Vec2<float> cam_pos = camera->getPosition() - Vec2<float>(m_scale, m_scale) / 2.0f;
        seg.a.x -= cam_pos.x;
        seg.a.y -= cam_pos.y;
        seg.b.x -= cam_pos.x;
        seg.b.y -= cam_pos.y;
    }

    seg.a.x = static_cast<int>(seg.a.x);
    seg.a.y = static_cast<int>(seg.a.y);
    seg.b.x = static_cast<int>(seg.b.x);
    seg.b.y = static_cast<int>(seg.b.y);

    SDL_RenderLine(m_renderer, seg.a.x, seg.a.y, seg.b.x, seg.b.y);

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
}