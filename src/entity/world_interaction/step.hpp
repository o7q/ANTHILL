#pragma once

#include "px/math/geometry/vec.hpp"
#include "entity/collider/entity_collider.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
struct StepResponse
{
    Vec2i moveVector;
};

struct StepDirectionalData
{
    Vec2i sum;
    int distance = 0;
    bool moved   = false;
};

StepResponse calculateStep(Vec2i resolvedPosition, Vec2i originalEnd, const EntityCollider &collider,
                           const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
