#pragma once

#include "utils/math/constants.hpp"

namespace Utils
{
namespace Math
{
namespace Angle
{

inline float degreesToRadians(float degrees)
{
    return static_cast<float>(Constants::DEG_TO_RAD) * degrees;
}
inline float radiansToDegrees(float radians)
{
    return static_cast<float>(Constants::RAD_TO_DEG) * radians;
}
} // namespace Angle
} // namespace Math
} // namespace Utils
