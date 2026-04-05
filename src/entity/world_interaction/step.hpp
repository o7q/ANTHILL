#pragma once

#include "math/rectangle.hpp"
#include "math/vec.hpp"
#include "world/particle_world/particle_world.hpp"

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
    bool moved = false;
};

StepResponse calculateStep(Vec2i resolvedPosition, Vec2i originalEnd,
                           const StaticGridRectangle &boundingBox,
                           const ParticleWorld &world);
} // namespace EntityWorldInteraction
