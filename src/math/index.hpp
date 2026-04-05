#pragma once

#include "math/vec.hpp"

namespace Math
{
namespace Index
{
inline unsigned int index_2dto1d(Vec2u index, unsigned int matrix_width)
{
    return index.y * matrix_width + index.x;
}

inline Vec2u index_1dTo2d(unsigned int index, unsigned int width)
{
    return Vec2u(index % width, index / width);
}
} // namespace Indicies
} // namespace Math
