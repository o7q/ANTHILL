#pragma once

#include "math/vec.hpp"

namespace Math
{
namespace Index
{
inline unsigned int index_2dto1d(unsigned int x, unsigned int y,
                                 unsigned int matrix_width)
{
    return y * matrix_width + x;
}

inline Vec2u index_1dTo2d(unsigned int index, unsigned int width)
{
    return Vec2u(index % width, index / width);
}
} // namespace Index
} // namespace Math
