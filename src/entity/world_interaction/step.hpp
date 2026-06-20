#pragma once

#include "px/basic_types/vec.hpp"
#include "entity/collider/entity_collider.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
struct StepResponse
{
    px::Vec2i moveVector;
};

struct StepDirectionalData
{
    px::Vec2i sum;
    int distance = 0;
    bool moved   = false;
};

StepResponse calculateStep(px::Vec2i resolvedPosition, px::Vec2i originalEnd, const EntityCollider &collider,
                           const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
