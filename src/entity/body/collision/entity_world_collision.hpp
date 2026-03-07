#pragma once

#include "backend/types/vec.hpp"
#include "types/bounding_box.hpp"
#include "world/world.hpp"

class EntityWorldCollisionHandler
{
  public:
    struct TrajectoryCollisionResponse
    {
        Vec2<int> resolvePos = Vec2<int>(0, 0);
        bool collided = false;
    };

    struct MTVPenetrationResponse
    {
        int left = 0;
        int right = 0;
        int top = 0;
        int bottom = 0;

        Vec2<int> resolve;
    };

  public:
    EntityWorldCollisionHandler(World &world, BoundingBox &bb)
        : r_world(world), r_boundingBox(bb)
    {
    }

    MTVPenetrationResponse calculateWorldPenetration_MTV(Vec2<int> pos);
    Vec2<float> calculateWorldPenetration_averageDirection(Vec2<int> pos);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectory(Vec2<int> start, Vec2<int> end);

    bool againstSolidSurface(Vec2<int> pos, BoundingBox::Side side);
    bool againstSolidCorner(Vec2<int> pos, BoundingBox::Corner corner);

  private:
    World &r_world;
    BoundingBox &r_boundingBox;
};
