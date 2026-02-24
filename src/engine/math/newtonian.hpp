#pragma once

namespace Math
{
// https://en.wikipedia.org/wiki/Elastic_collision
inline float elasticCollisionVelocityA(float mA, float mB, float velA,
                                       float velB)
{
    float totalMass = mA + mB;
    return (mA - mB) / totalMass * velA + (2 * mB) / totalMass * velB;
}

inline float elasticCollisionVelocityB(float mA, float mB, float velA,
                                       float velB)
{
    float totalMass = mA + mB;
    return (mB - mA) / totalMass * velB + (2 * mA) / totalMass * velA;
}
}; // namespace Math
