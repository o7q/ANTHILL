#pragma once

#include "vec.hpp"
#include <algorithm>
#include <functional>
#include <vector>

namespace Utils
{
template <typename T>
inline bool doesVectorContain(const std::vector<T> &vector, const T &value)
{
    return std::find(vector.begin(), vector.end(), value) != vector.end();
}

template <typename T>
inline void removeItemFromVector(std::vector<T> &vector, const T &value)
{
    auto new_end = std::remove(vector.begin(), vector.end(), value);
    vector.erase(new_end, vector.end());
}

inline unsigned int index_2dto1d(unsigned int x, unsigned int y,
                                 unsigned int width)
{
    return y * width + x;
}

inline Vec2<unsigned int> index_1dTo2d(unsigned int index, unsigned int width)
{
    unsigned int x = index % width;
    unsigned int y = index / y;

    return Vec2<unsigned int>(x, y);
}

// https://stackoverflow.com/a/27952689
inline size_t hashCombine(size_t lhs, size_t rhs)
{
    return lhs ^ (rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2));
}

// https://stackoverflow.com/a/20602159
struct PairHash
{
  public:
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &p) const
    {
        return hashCombine(std::hash<T>()(p.first), std::hash<U>()(p.second));
    }
};

} // namespace Utils
