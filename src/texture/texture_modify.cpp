#include "texture.hpp"

#include <SDL3/SDL.h>

void Texture::setPixel(int x, int y, Uint32 color)
{
    if (x < 0 || y < 0 || x >= size.x || y >= size.y)
    {
        return;
    }

    const unsigned int index = y * size.x + x;
    pixels[index] = color;

    if (x < update_pos1.x)
    {
        update_pos1.x = x;
    }
    if (y < update_pos1.y)
    {
        update_pos1.y = y;
    }
    if (x > update_pos2.x)
    {
        update_pos2.x = x;
    }
    if (y > update_pos2.y)
    {
        update_pos2.y = y;
    }

    update_rect.x = update_pos1.x;
    update_rect.y = update_pos1.y;
    update_rect.w = update_pos2.x - update_pos1.x + 1;
    update_rect.h = update_pos2.y - update_pos1.y + 1;
}

void Texture::update()
{
    void *update_pixels = &pixels[update_rect.y * size.x + update_rect.x];
    SDL_UpdateTexture(texture, &update_rect, update_pixels, size.x * sizeof(Uint32));
    reset_update_rect();
}