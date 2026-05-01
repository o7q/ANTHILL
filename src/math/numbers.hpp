#pragma once

namespace Math
{
namespace Numbers
{
// https://stackoverflow.com/a/4609795
template <typename T> inline int sign(T v) { return (T(0) < v) - (v < T(0)); }

template <typename T> inline bool between(T v, T min, T max) { return v >= min && v <= max; }
} // namespace Numbers
} // namespace Math
