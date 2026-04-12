#pragma once

#include <cstdint>

struct Color
{
    uint8_t r = 0, g = 0, b = 0, a = 0;

    Color() = default;
    Color(uint8_t c, uint8_t a_ = 255) : r(c), g(c), b(c), a(a_) {}
    Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 255)
        : r(r_), g(g_), b(b_), a(a_)
    {
    }

    template <typename T> Color operator*(T v)
    {
        return Color(r * v, g * v, b * v);
    }
};
