#pragma once

#include "math/rectangle.hpp"
#include "math/vec.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
struct MTVIntersectionResponse
{
    int left = 0;
    int right = 0;
    int top = 0;
    int bottom = 0;

    int resolveDistance = 0;

    Vec2i moveVector;
};

MTVIntersectionResponse
calculateWorldIntersection_MTV(Vec2i pos,
                               const StaticGridRectangle &boundingBox,
                               const ParticleHandler &particleHandler);

Vec2f calculateWorldIntersection_averageDirection(
    Vec2i pos, const StaticGridRectangle &boundingBox,
    const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
