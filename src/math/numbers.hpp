#pragma once

namespace Math
{
namespace Numbers
{
// https://stackoverflow.com/a/4609795
template <typename T> inline int sign(T v) { return (T(0) < v) - (v < T(0)); }

template <typename T> T clamp(T value, T min, T max)
{
    return value < min ? min : (value > max ? max : value);
}
} // namespace Numbers
} // namespace Math
