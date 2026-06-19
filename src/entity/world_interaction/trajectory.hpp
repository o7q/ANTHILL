#pragma once

#include "px/math/geometry/vec.hpp"
#include "entity/collider/entity_collider.hpp"
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
                                                             const EntityCollider &collider,
                                                             const ParticleHandler &particleHandler);

TrajectoryCollisionResponse calculateCollisionFromTrajectorySlide(Vec2i start, Vec2i end,
                                                                  const EntityCollider &collider,
                                                                  const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
