#pragma once

namespace Utils
{
namespace Math
{
namespace Numbers
{
// https://stackoverflow.com/a/4609795
template <typename T> inline int sign(T v) { return (T(0) < v) - (v < T(0)); }
} // namespace Numbers
} // namespace Math
} // namespace Utils
