#pragma once

#include "backend/types/vec.hpp"
#include "types/bounding_box.hpp"
#include "world/world.hpp"

class WorldCollisionHandler
{
  public:
    struct TrajectoryCollisionResponse
    {
        Vec2<int> resolvePos = Vec2<int>(0, 0);
        bool collided = false;
    };

  public:
    WorldCollisionHandler(World &world) : r_world(world) {}

    Vec2<int> calculateWorldPenetration_MTV(Vec2<int> pos);
    Vec2<float> calculateWorldPenetration_averageDirection(Vec2<int> pos);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectory(Vec2<int> start, Vec2<int> end);

    bool againstSolidSurface(Vec2<int> pos, BoundingBox::Side side);

    BoundingBox &getCollisionBox() { return m_collisionBox; }

  private:
    World &r_world;
    BoundingBox m_collisionBox;
};
