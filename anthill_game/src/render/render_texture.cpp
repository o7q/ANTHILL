#include "render_manager.hpp"

void RenderManager::renderTexture(const Texture &texture, const Camera *camera)
{
    const SDL_FRect *texture_dst_rect = texture.getSDLDstRect();

    SDL_FRect new_dst_rect;
    new_dst_rect.x = texture_dst_rect->x;
    new_dst_rect.y = texture_dst_rect->y;
    new_dst_rect.w = texture_dst_rect->w;
    new_dst_rect.h = texture_dst_rect->h;

    if (camera != nullptr)
    {
        Vec2<int> cam_pos = camera->getPosition() - Vec2<int>(m_scale, m_scale) / 2.0f;
        new_dst_rect.x -= cam_pos.x;
        new_dst_rect.y -= cam_pos.y;
    }

    new_dst_rect.x = static_cast<int>(new_dst_rect.x);
    new_dst_rect.y = static_cast<int>(new_dst_rect.y);
    new_dst_rect.w = static_cast<int>(new_dst_rect.w);
    new_dst_rect.h = static_cast<int>(new_dst_rect.h);

    SDL_RenderTextureRotated(m_renderer,
                             texture.getSDLTexture(),
                             texture.getSDLSrcRect(),
                             &new_dst_rect,
                             0,
                             NULL,
                             texture.getSDLFlipMode());
}