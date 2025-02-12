#include "render_manager.hpp"

void RenderManager::debug_renderPoint(int x, int y, Color color, const Camera *camera)
{
    if (camera != nullptr)
    {
        Vec2<int> cam_pos = camera->getPosition().toInt();
        x -= cam_pos.x;
        y -= cam_pos.y;
    }

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_renderer, x, y);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
}