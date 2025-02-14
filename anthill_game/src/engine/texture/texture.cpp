#include "texture.hpp"

#include <string>
#include <cstring>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Texture::Texture(SDL_Renderer *renderer, const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    SDL_Surface *formatted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA8888);
    m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formatted->w, formatted->h);

    const unsigned int pixel_count = formatted->w * formatted->h;
    m_pixels = new Uint32[pixel_count];
    std::memcpy(m_pixels, formatted->pixels, pixel_count * sizeof(Uint32));

    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(m_texture, NULL, formatted->pixels, formatted->pitch);

    m_size.x = formatted->w;
    m_size.y = formatted->h;

    m_origin.x = formatted->w / 2;
    m_origin.y = formatted->h / 2;

    SDL_DestroySurface(surface);
    SDL_DestroySurface(formatted);

    update_sdl_transforms();
}

Texture::Texture(SDL_Renderer *renderer, SDL_Surface *surface)
{
    SDL_Surface *formatted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA8888);
    m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formatted->w, formatted->h);

    const unsigned int pixel_count = formatted->w * formatted->h;
    m_pixels = new Uint32[pixel_count];
    std::memcpy(m_pixels, formatted->pixels, pixel_count * sizeof(Uint32));

    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(m_texture, NULL, formatted->pixels, formatted->pitch);

    m_size.x = formatted->w;
    m_size.y = formatted->h;

    m_origin.x = formatted->w / 2;
    m_origin.y = formatted->h / 2;

    SDL_DestroySurface(formatted);

    update_sdl_transforms();
}

Texture::Texture(SDL_Renderer *renderer, int width, int height)
{
    m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    m_pixels = new Uint32[width * height];
    for (int i = 0; i < width * height; ++i)
        m_pixels[i] = 0xFFFFFFFF;

    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(m_texture, NULL, m_pixels, width * sizeof(Uint32));

    m_size.x = width;
    m_size.y = height;

    m_origin.x = width / 2;
    m_origin.y = height / 2;

    update_sdl_transforms();
}

Texture::~Texture()
{
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
    if (m_pixels != nullptr)
    {
        delete[] m_pixels;
        m_pixels = nullptr;
    }
}

void Texture::setPosition(int x, int y)
{
    m_position.x = x;
    m_position.y = y;
    update_sdl_transforms();
}

void Texture::setOrigin(int x, int y)
{
    m_origin.x = x;
    m_origin.y = y;
    update_sdl_transforms();
}

void Texture::move(int x, int y)
{
    m_position.x += x;
    m_position.y += y;
    update_sdl_transforms();
}

void Texture::setFlipMode(SDL_FlipMode flip_mode)
{
    this->m_flip_mode = flip_mode;
}