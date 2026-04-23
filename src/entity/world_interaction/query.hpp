#pragma once

#include "math/rectangle.hpp"
#include "math/vec.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
struct LocalWorldQuery
{
    int staticSolidCount = 0;
};

LocalWorldQuery generateLocalWorldQuery(Vec2i pos,
                                        const StaticGridRectangle &boundingBox,
                                        const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
