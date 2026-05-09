#pragma once

#include <algorithm>
#include <vector>

namespace Utils
{
namespace Data
{
template <typename T> inline bool doesVectorContain(const std::vector<T> &vector, const T &value)
{
    return std::find(vector.begin(), vector.end(), value) != vector.end();
}

template <typename T> inline void removeItemFromVector(std::vector<T> &vector, const T &value)
{
    auto new_end = std::remove(vector.begin(), vector.end(), value);
    vector.erase(new_end, vector.end());
}
} // namespace Data
} // namespace Utils
