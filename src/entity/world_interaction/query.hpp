#pragma once

#include "core/math/vec.hpp"
#include "entity/collider/entity_collider.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
struct LocalWorldQuery
{
    int staticSolidCount = 0;
};

LocalWorldQuery generateLocalWorldQuery(Vec2i pos, const EntityCollider &collider,
                                        const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
