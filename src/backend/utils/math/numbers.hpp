#pragma once

namespace Backend
{
namespace Utils
{
namespace Math
{
namespace Numbers
{
template <typename T> T clamp(T value, T min, T max)
{
    return value < min ? min : (value > max ? max : value);
}
} // namespace Numbers
} // namespace Math
} // namespace Utils
} // namespace Backend
