#include "render_manager.hpp"

void RenderManager::debug_renderPoint(int x, int y, Color color, const Camera *camera)
{
    if (camera != nullptr)
    {
        Vec2<float> cam_pos = camera->getPosition() - Vec2<float>(m_scale, m_scale) / 2.0f;;
        x -= cam_pos.x;
        y -= cam_pos.y;
    }

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_renderer, x, y);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
}