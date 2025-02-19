#pragma once

#include <SDL3/SDL.h>

struct Color
{
    Color() = default;
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) : r(r), g(g), b(b), a(a) {}

    Uint32 hex() const;

    Uint8 r = 0, g = 0, b = 0, a = 0;
};