#pragma once

#include "math/rectangle.hpp"
#include "math/vec.hpp"
#include "world/particle/particle_world.hpp"

namespace EntityWorldInteraction
{
bool againstSolidSurface(Vec2i pos, const StaticGridRectangle &boundingBox,
                         const ParticleWorld &world, RectangleSide side);

bool againstSolidCorner(Vec2i pos, const StaticGridRectangle &boundingBox,
                        const ParticleWorld &world, RectangleCorner corner);
} // namespace EntityWorldInteraction
