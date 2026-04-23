#pragma once

#include "math/rectangle.hpp"
#include "math/vec.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
bool againstSolidSurface(Vec2i pos, const StaticGridRectangle &boundingBox,
                         const ParticleHandler &particleHandler,
                         RectangleSide side);

bool againstSolidCorner(Vec2i pos, const StaticGridRectangle &boundingBox,
                        const ParticleHandler &particleHandler,
                        RectangleCorner corner);
} // namespace EntityWorldInteraction
