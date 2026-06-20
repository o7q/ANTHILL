#pragma once

#include "px/basic_types/vec.hpp"
#include "entity/collider/entity_collider.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
struct LocalWorldQuery
{
    int staticSolidCount = 0;
};

LocalWorldQuery generateLocalWorldQuery(px::Vec2i pos, const EntityCollider &collider,
                                        const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
