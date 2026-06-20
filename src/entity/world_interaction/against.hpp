#pragma once

#include "entity/collider/entity_collider.hpp"
#include "px/basic_types/rectangle.hpp"
#include "px/basic_types/vec.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
bool againstSolidSurface(px::Vec2i pos, const EntityCollider &collider,
                         const ParticleHandler &particleHandler, px::RectangleSide side);

bool againstSolidCorner(px::Vec2i pos, const EntityCollider &collider, const ParticleHandler &particleHandler,
                        px::RectangleCorner corner);
} // namespace EntityWorldInteraction
