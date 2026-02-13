#pragma once

#include <algorithm>
#include <vector>

namespace Utils
{
template <typename T>
inline bool doesVectorContain(std::vector<T> vector, T value)
{
    return std::find(vector.begin(), vector.end(), value) != vector.end();
}
} // namespace Utils
