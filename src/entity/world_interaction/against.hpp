#pragma once

#include "px/math/geometry/rectangle.hpp"
#include "px/math/geometry/vec.hpp"
#include "entity/collider/entity_collider.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
bool againstSolidSurface(Vec2i pos, const EntityCollider &collider, const ParticleHandler &particleHandler,
                         RectangleSide side);

bool againstSolidCorner(Vec2i pos, const EntityCollider &collider, const ParticleHandler &particleHandler,
                        RectangleCorner corner);
} // namespace EntityWorldInteraction
