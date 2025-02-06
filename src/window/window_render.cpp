#include "window.hpp"

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
        Vec2<int> cam_pos = camera->getPosition();
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

void Window::renderText(const std::string &text, Vec2<int> position, Color color, Camera *camera)
{
    SDL_Surface *surface = TTF_RenderText_Solid(m_font, text.c_str(), text.size(), SDL_Color{color.r, color.g, color.b, color.a});

    Texture texture(m_renderer, surface);
    texture.setPosition(position.x, position.y);
    texture.setOrigin(0, 0);
    SDL_DestroySurface(surface);

    renderTexture(texture, camera);
}

void Window::debug_renderBoundingBox(const BoundingBox &boundingBox, Uint8 r, Uint8 g, Uint8 b, Uint8 a, const Camera *camera)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);

    Vec2<int> top_left = boundingBox.getP1();
    Vec2<int> size = boundingBox.getSize();

    SDL_FRect rect;
    rect.x = top_left.x;
    rect.y = top_left.y;
    rect.w = size.x;
    rect.h = size.y;

    if (camera != nullptr)
    {
        Vec2<int> cam_pos = camera->getPosition();
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

void Window::debug_renderSegment(const Segment &segment, Uint8 r, Uint8 g, Uint8 b, Uint8 a, const Camera *camera)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);

    Segment seg = segment;

    if (camera != nullptr)
    {
        Vec2<int> cam_pos = camera->getPosition();
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

void Window::debug_renderPoint(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, const Camera *camera)
{
    if (camera != nullptr)
    {
        Vec2<int> cam_pos = camera->getPosition();
        x -= cam_pos.x;
        y -= cam_pos.y;
    }

    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    SDL_RenderPoint(m_renderer, x, y);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
}