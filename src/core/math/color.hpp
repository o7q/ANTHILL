#pragma once

#include <cstdint>

struct Color
{
    uint8_t r = 0, g = 0, b = 0, a = 0;

    Color() = default;
    Color(uint32_t embed)
    {
        r = static_cast<uint8_t>(embed >> 24);
        g = static_cast<uint8_t>(embed >> 16);
        b = static_cast<uint8_t>(embed >> 8);
        a = static_cast<uint8_t>(embed);
    }
    Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 255) : r(r_), g(g_), b(b_), a(a_) {}

    uint32_t embed() const
    {
        return static_cast<uint32_t>(r) << 24 | static_cast<uint32_t>(g) << 16 |
               static_cast<uint32_t>(b) << 8 | static_cast<uint32_t>(a);
    }
};
