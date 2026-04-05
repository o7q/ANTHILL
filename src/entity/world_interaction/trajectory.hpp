#pragma once

#include "math/rectangle.hpp"
#include "math/vec.hpp"
#include "world/particle_world/particle_world.hpp"

namespace EntityWorldInteraction
{
struct TrajectoryCollisionResponse
{
    Vec2i hitPosition;
    Vec2i resolvePosition;
    bool collided = false;
};

TrajectoryCollisionResponse
calculateCollisionFromTrajectory(Vec2i start, Vec2i end,
                                 const StaticGridRectangle &boundingBox,
                                 const ParticleWorld &world);

TrajectoryCollisionResponse
calculateCollisionFromTrajectorySlide(Vec2i start, Vec2i end,
                                      const StaticGridRectangle &boundingBox,
                                      const ParticleWorld &world);
} // namespace EntityWorldInteraction
