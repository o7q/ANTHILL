#pragma once

#include <SDL3/SDL.h>

template <typename T>
struct Vec2
{
    Vec2() = default;
    Vec2(T x, T y) : x(x), y(y) {}

    Vec2<T> operator+(const Vec2<T> &other) const
    {
        return Vec2<T>(x + other.x, y + other.y);
    }

    Vec2<T> operator-(const Vec2<T> &other) const
    {
        return Vec2<T>(x - other.x, y - other.y);
    }

    Vec2<T> operator*(const Vec2<T> &other) const
    {
        return Vec2<T>(x * other.x, y * other.y);
    }

    Vec2<T> operator/(const Vec2<T> &other) const
    {
        return Vec2<T>(x / other.x, y / other.y);
    }

    T x = 0, y = 0;
};

struct Color
{
    Color() = default;
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a) {}

    Uint32 hex() const
    {
        SDL_PixelFormatDetails pfd;
        pfd.format = SDL_PIXELFORMAT_RGBA8888;
        return SDL_MapRGBA(&pfd, NULL, r, g, b, a);
    }

    Uint8 r = 255, g = 255, b = 255, a = 255;
};