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

inline Vec2<unsigned int> index_1dTo2d(unsigned int index, unsigned int width)
{
    unsigned int x = index % width;
    unsigned int y = index / width;

    return Vec2<unsigned int>(x, y);
}
} // namespace Index
} // namespace Math
