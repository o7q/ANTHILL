#include "angle.hpp"

#include "constants.hpp"

float radiansToDegrees(float radians)
{
    return radians * (180.0f / PI);
}

float degreesToRadians(float degrees)
{
    return degrees * (PI / 180.0f);
}