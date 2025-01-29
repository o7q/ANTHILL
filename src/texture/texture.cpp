#include "texture.hpp"

#include <string>
#include <cstring>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Texture::Texture(SDL_Renderer *renderer, const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    SDL_Surface *formatted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA8888);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formatted->w, formatted->h);

    const unsigned int pixel_count = formatted->w * formatted->h;
    pixels = new Uint32[pixel_count];
    std::memcpy(pixels, formatted->pixels, pixel_count * sizeof(Uint32));

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(texture, NULL, formatted->pixels, formatted->pitch);

    size.x = formatted->w;
    size.y = formatted->h;

    SDL_DestroySurface(surface);
    SDL_DestroySurface(formatted);

    update_sdl_transforms();
}

Texture::Texture(SDL_Renderer *renderer, unsigned int width, unsigned int height)
{
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    pixels = new Uint32[width * height];
    for (unsigned int i = 0; i < width * height; ++i)
        pixels[i] = 0xFFFFFFFF;

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));

    size.x = width;
    size.y = height;

    update_sdl_transforms();
}

Texture::~Texture()
{
    if (texture != nullptr)
        SDL_DestroyTexture(texture);
    if (pixels != nullptr)
        delete[] pixels;
}

void Texture::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
    update_sdl_transforms();
}

void Texture::move(int x, int y)
{
    position.x += x;
    position.y += y;
    update_sdl_transforms();
}

void Texture::setFlipMode(SDL_FlipMode flip_mode)
{
    this->flip_mode = flip_mode;
}