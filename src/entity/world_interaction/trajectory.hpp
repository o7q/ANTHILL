#pragma once

#include "px/basic_types/vec.hpp"
#include "entity/collider/entity_collider.hpp"
#include "world/particle_handler/particle_handler.hpp"

namespace EntityWorldInteraction
{
struct TrajectoryCollisionResponse
{
    px::Vec2i hitPosition;
    px::Vec2i resolvePosition;
    bool collided = false;
};

TrajectoryCollisionResponse calculateCollisionFromTrajectory(px::Vec2i start, px::Vec2i end,
                                                             const EntityCollider &collider,
                                                             const ParticleHandler &particleHandler);

TrajectoryCollisionResponse calculateCollisionFromTrajectorySlide(px::Vec2i start, px::Vec2i end,
                                                                  const EntityCollider &collider,
                                                                  const ParticleHandler &particleHandler);
} // namespace EntityWorldInteraction
