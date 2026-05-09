#pragma once

#include "core/math/rectangle.hpp"
#include "core/math/vec.hpp"
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

StepResponse calculateStep(Vec2i resolvedPosition, Vec2i originalEnd, const StaticGridRectangle &boundingBox,
                           const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
