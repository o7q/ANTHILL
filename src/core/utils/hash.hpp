#pragma once

#include <cstddef>

namespace Utils
{
namespace Hash
{
// https://stackoverflow.com/a/27952689
inline size_t hashCombine(size_t lhs, size_t rhs)
{
    return lhs ^ (rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2));
}
} // namespace Hash
} // namespace Utils
