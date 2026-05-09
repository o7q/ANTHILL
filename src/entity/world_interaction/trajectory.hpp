#pragma once

#include "core/math/rectangle.hpp"
#include "core/math/vec.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
struct TrajectoryCollisionResponse
{
    Vec2i hitPosition;
    Vec2i resolvePosition;
    bool collided = false;
};

TrajectoryCollisionResponse calculateCollisionFromTrajectory(Vec2i start, Vec2i end,
                                                             const StaticGridRectangle &boundingBox,
                                                             const ParticleHandler &particleHandler);

TrajectoryCollisionResponse calculateCollisionFromTrajectorySlide(Vec2i start, Vec2i end,
                                                                  const StaticGridRectangle &boundingBox,
                                                                  const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
