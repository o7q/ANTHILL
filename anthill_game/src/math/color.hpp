#pragma once

#include <SDL3/SDL.h>

struct Color
{
    Color() = default;
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) : r(r), g(g), b(b), a(a) {}

    Uint32 hex() const
    {
        return (static_cast<Uint32>(r) << 24) |
               (static_cast<Uint32>(g) << 16) |
               (static_cast<Uint32>(b) << 8) |
               (static_cast<Uint32>(a));
    }

    Uint8 r = 0, g = 0, b = 0, a = 0;
};