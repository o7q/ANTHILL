#include "render_manager.hpp"

void RenderManager::debug_renderPoint(int x, int y, Color color, const Camera *camera)
{
    if (camera != nullptr)
    {
        Vec2<float> cam_pos = camera->getPosition() - Vec2<float>(m_scaled_size.x, m_scaled_size.y) / 2.0f;;
        x -= cam_pos.x;
        y -= cam_pos.y;
    }

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_renderer, x, y);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
}