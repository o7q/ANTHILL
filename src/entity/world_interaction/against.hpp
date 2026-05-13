#pragma once

#include "core/math/rectangle.hpp"
#include "core/math/vec.hpp"
#include "entity/collider/entity_collider.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
bool againstSolidSurface(Vec2i pos, const EntityCollider &collider, const ParticleHandler &particleHandler,
                         RectangleSide side);

bool againstSolidCorner(Vec2i pos, const EntityCollider &collider, const ParticleHandler &particleHandler,
                        RectangleCorner corner);
} // namespace EntityWorldInteraction
