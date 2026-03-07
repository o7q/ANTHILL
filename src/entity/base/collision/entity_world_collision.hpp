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

    struct MTVIntersectionResponse
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

    MTVIntersectionResponse calculateWorldIntersection_MTV(Vec2<int> pos);
    Vec2<float> calculateWorldIntersection_averageDirection(Vec2<int> pos);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectory(Vec2<int> start, Vec2<int> end);

    bool againstSolidSurface(Vec2<int> pos, BoundingBox::Side side);
    bool againstSolidCorner(Vec2<int> pos, BoundingBox::Corner corner);

    Vec2<int> calculateStepPosition(Vec2<int> pos, Vec2<float> velocity)
    {
        Vec2<int> out = pos;
        bool blockedLeft = againstSolidSurface(pos, BoundingBox::Side::Left);
        bool blockedRight = againstSolidSurface(pos, BoundingBox::Side::Right);

        if ((blockedLeft && velocity.x < 0.0f) ||
            (blockedRight && velocity.x > 0.0f))
        {
            for (int step = 1; step <= 3; ++step)
            {
                Vec2<int> steppedPos = {pos.x, pos.y - step};

                bool stillBlockedRight =
                    blockedRight &&
                    againstSolidSurface(steppedPos, BoundingBox::Side::Right);
                bool stillBlockedLeft =
                    blockedLeft &&
                    againstSolidSurface(steppedPos, BoundingBox::Side::Left);

                if (!stillBlockedRight && !stillBlockedLeft)
                {
                    EntityWorldCollisionHandler::TrajectoryCollisionResponse
                        test =
                            calculateCollisionFromTrajectory(pos, steppedPos);
                    if (test.collided)
                    {
                        break;
                    }
                    out = steppedPos;
                    blockedRight = false;
                    blockedLeft = false;
                    break;
                }
            }
        }

        return out;
    }

    Vec2<int> calculateAvoidedWorldCollisionPosition(Vec2<int> start,
                                                     Vec2<int> end)
    {
        Vec2<int> out = start;

        TrajectoryCollisionResponse xy_response =
            calculateCollisionFromTrajectory(start, end);

        // all axis
        if (xy_response.collided)
        {
            // horizontal axis
            Vec2<int> end_x = {end.x, xy_response.resolvePos.y};
            TrajectoryCollisionResponse x_response =
                calculateCollisionFromTrajectory(xy_response.resolvePos, end_x);

            if (xy_response.resolvePos == x_response.resolvePos)
            {
                // vertical axis
                Vec2<int> end_y = {xy_response.resolvePos.x, end.y};
                TrajectoryCollisionResponse y_response =
                    calculateCollisionFromTrajectory(xy_response.resolvePos,
                                                     end_y);

                out = y_response.resolvePos;
            }
            else
            {
                out = x_response.resolvePos;
            }
        }

        return out;
    }

  private:
    World &r_world;
    BoundingBox &r_boundingBox;
};
