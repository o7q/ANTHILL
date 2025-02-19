#include "color.hpp"

Uint32 Color::hex() const
{
    return (static_cast<Uint32>(r) << 24) |
           (static_cast<Uint32>(g) << 16) |
           (static_cast<Uint32>(b) << 8) |
           (static_cast<Uint32>(a));
}