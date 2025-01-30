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

void Window::debug_renderBoundingBox(const BoundingBox &boundingBox, Uint8 r, Uint8 g, Uint8 b, Uint8 a, const Camera *camera)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);

    Vec2<float> top_left = boundingBox.getP1();
    Vec2<float> size = boundingBox.getSize();

    SDL_FRect rect;
    rect.x = top_left.x;
    rect.y = top_left.y;
    rect.w = size.x;
    rect.h = size.y;

    if (camera != nullptr)
    {
        Vec2<int> position = camera->getPosition();
        rect.x -= position.x;
        rect.y -= position.y;
    }

    SDL_RenderRect(m_renderer, &rect);

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
}