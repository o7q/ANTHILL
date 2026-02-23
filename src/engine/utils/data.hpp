#pragma once

#include <algorithm>
#include <vector>

namespace DataUtils
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
} // namespace DataUtils
