#pragma once

#include "px/basic_types/vec.hpp"
#include "entity/collider/entity_collider.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
struct MTVIntersectionResponse
{
    int left   = 0;
    int right  = 0;
    int top    = 0;
    int bottom = 0;

    int resolveDistance = 0;

    px::Vec2i moveVector;
};

MTVIntersectionResponse calculateWorldIntersection_MTV(px::Vec2i pos, const EntityCollider &collider,
                                                       const ParticleHandler &particleHandler);

px::Vec2f calculateWorldIntersection_averageDirection(px::Vec2i pos, const EntityCollider &collider,
                                                  const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
