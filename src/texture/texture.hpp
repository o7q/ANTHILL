#pragma once

#include <string>

#include <SDL3/SDL.h>

#include "../math/vector.hpp"

class Texture
{
public:
    Texture(SDL_Renderer *renderer, const std::string &path);

    Texture(SDL_Renderer *renderer, unsigned int width, unsigned int height);

    ~Texture();

    void setPixel(int x, int y, Uint32 color);
    void update();

    void setPosition(int x, int y);
    void move(int x, int y);
    void setFlipMode(SDL_FlipMode flip_mode);

    Vec2<int> getPosition() const { return position; }

    SDL_Texture *getSDLTexture() const { return texture; }
    const SDL_FRect *getSDLSrcRect() const { return &src_rect; }
    const SDL_FRect *getSDLDstRect() const { return &dst_rect; }
    const SDL_FPoint *getSDLCenterPoint() const { return &center_point; }
    const SDL_FlipMode getSDLFlipMode() const { return flip_mode; }

private:
    void update_sdl_transforms();
    void reset_update_rect();

private:
    Vec2<int> position;
    Vec2<int> size;

    Vec2<int> update_pos1;
    Vec2<int> update_pos2;

    SDL_FlipMode flip_mode = SDL_FLIP_NONE;

    SDL_FRect src_rect;
    SDL_FRect dst_rect;
    SDL_FPoint center_point;

    SDL_Rect update_rect;
    Uint32 *pixels = nullptr;
    SDL_Texture *texture = nullptr;
};