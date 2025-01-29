#include "window.hpp"

#include <iostream>

void Window::renderTexture(const Texture &texture, const Camera *camera)
{
    const SDL_FRect *texture_dst_rect = texture.getSDLDstRect();

    SDL_FRect new_dst_rect;
    new_dst_rect.x = texture_dst_rect->x;
    new_dst_rect.y = texture_dst_rect->y;
    new_dst_rect.w = texture_dst_rect->w;
    new_dst_rect.h = texture_dst_rect->h;

    if (camera != nullptr)
    {
        Vec2<int> position = camera->getPosition();
        new_dst_rect.x -= position.x;
        new_dst_rect.y -= position.y;
    }

    SDL_RenderTextureRotated(m_renderer,
                             texture.getSDLTexture(),
                             texture.getSDLSrcRect(),
                             &new_dst_rect,
                             0,
                             texture.getSDLCenterPoint(),
                             texture.getSDLFlipMode());
}