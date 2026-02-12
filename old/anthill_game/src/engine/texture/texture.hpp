#pragma once

#include <string>

#include <SDL3/SDL.h>

#include "../math/vector.hpp"

class Texture
{
public:
    Texture(SDL_Renderer *renderer, const std::string &path);
    Texture(SDL_Renderer *renderer, SDL_Surface *surface);
    Texture(SDL_Renderer *renderer, int width, int height);

    ~Texture();

    void setPixel(int x, int y, Uint32 color);
    void update();

    void setPosition(int x, int y);
    void setOrigin(int x, int y);
    void move(int x, int y);
    void setFlipMode(SDL_FlipMode flip_mode);

    Vec2<int> getPosition() const { return m_position; }

    SDL_Texture *getSDLTexture() const { return m_texture; }
    const SDL_FRect *getSDLSrcRect() const { return &m_src_rect; }
    const SDL_FRect *getSDLDstRect() const { return &m_dst_rect; }
    const SDL_FlipMode getSDLFlipMode() const { return m_flip_mode; }

    const SDL_Rect getSDLUpdateRect() const {return m_update_rect;}

private:
    void update_sdl_transforms();
    void reset_update_points();

private:
    Vec2<int> m_position;
    Vec2<int> m_size;
    Vec2<int> m_origin;

    Vec2<int> m_update_pos1;
    Vec2<int> m_update_pos2;

    SDL_FlipMode m_flip_mode = SDL_FLIP_NONE;

    SDL_FRect m_src_rect;
    SDL_FRect m_dst_rect;

    SDL_Rect m_update_rect;
    Uint32 *m_pixels = nullptr;
    SDL_Texture *m_texture = nullptr;

    bool m_pixel_changed = false;
};