#include "world_interaction.hpp"

#include "math/line.hpp"
#include "math/numbers.hpp"

WorldInteractionHandler::TrajectoryCollisionResponse
WorldInteractionHandler::calculateCollisionFromTrajectory(
    Vec2i start, Vec2i end, const ParticleWorld &world)
{
    bool collided = false;
    Vec2i previousPos = start;

    auto check = [&](Vec2i pos)
    {
        Vec2i a = r_boundingBox.getA() + pos;
        Vec2i b = r_boundingBox.getB() + pos;

        bool collidedThisIteration = false;
        auto query = [&](const Particle *p)
        {
            if (p->isSolid() && !p->isMoving())
            {
                collidedThisIteration = true;
                return true;
            }

            return false;
        };
        world.query(a, b, query);

        if (collidedThisIteration)
        {
            collided = true;
            return true;
        }

        previousPos = pos;

        return false;
    };

    Math::Line::bresenhamLine(start, end, check);

    TrajectoryCollisionResponse response;
    response.collided = collided;
    response.resolvePosition = previousPos;
    return response;
}

WorldInteractionHandler::TrajectoryCollisionResponse
WorldInteractionHandler::calculateCollisionFromTrajectorySlide(
    Vec2i start, Vec2i end, const ParticleWorld &world)
{
    TrajectoryCollisionResponse out;

    TrajectoryCollisionResponse xy_response =
        calculateCollisionFromTrajectory(start, end, world);

    // all axis
    if (xy_response.collided)
    {
        // horizontal axis
        Vec2i end_x = {end.x, xy_response.resolvePosition.y};
        TrajectoryCollisionResponse x_response =
            calculateCollisionFromTrajectory(xy_response.resolvePosition, end_x,
                                             world);

        if (x_response.collided)
        {
            // vertical axis
            Vec2i end_y = {xy_response.resolvePosition.x, end.y};
            TrajectoryCollisionResponse y_response =
                calculateCollisionFromTrajectory(xy_response.resolvePosition,
                                                 end_y, world);

            out.resolvePosition = y_response.resolvePosition;
        }
        else
        {
            out.resolvePosition = x_response.resolvePosition;
        }

        out.collided = true;
    }

    return out;
}

WorldInteractionHandler::StepResponse WorldInteractionHandler::calculateStep(
    Vec2i resolvedPosition, Vec2i originalEnd, const ParticleWorld &world)
{
    StepResponse response;

    int amount = originalEnd.x - resolvedPosition.x;
    int dir = Math::Numbers::sign(amount);

    int maxStepAmount = 3;

    StepDirectionalData stepUpwards;
    StepDirectionalData stepDownwards;

    for (int i = 1; i <= std::abs(amount); ++i)
    {
        int step = i * dir;

        Vec2i upwardsCheckPos = {resolvedPosition.x + step,
                                 resolvedPosition.y + stepUpwards.sum.y};
        Vec2i downwardsCheckPos = {resolvedPosition.x + step,
                                   resolvedPosition.y + stepDownwards.sum.y};

        MTVIntersectionResponse upwardsCheck =
            calculateWorldIntersection_MTV(upwardsCheckPos, world);

        MTVIntersectionResponse downwardsCheck =
            calculateWorldIntersection_MTV(downwardsCheckPos, world);

        Vec2i upwardsNextPos = upwardsCheckPos + Vec2i(0, -upwardsCheck.bottom);
        Vec2i downwardsNextPos =
            downwardsCheckPos + Vec2i(0, downwardsCheck.top);

        if (upwardsCheck.bottom <= maxStepAmount &&
            calculateWorldIntersection_MTV(upwardsNextPos, world)
                    .resolveDistance == 0)
        {
            stepUpwards.sum.x = step;
            stepUpwards.sum.y -= upwardsCheck.bottom;
            stepUpwards.distance += upwardsCheck.bottom;
            stepUpwards.moved = true;
        }

        if (downwardsCheck.top <= maxStepAmount &&
            calculateWorldIntersection_MTV(downwardsNextPos, world)
                    .resolveDistance == 0)
        {
            stepDownwards.sum.x = step;
            stepDownwards.sum.y += downwardsCheck.top;
            stepDownwards.distance += downwardsCheck.top;
            stepDownwards.moved = true;
        }
    }

    if (stepUpwards.moved && !stepDownwards.moved)
    {
        response.moveVector = stepUpwards.sum;
    }
    if (stepDownwards.moved && !stepUpwards.moved)
    {
        response.moveVector = stepDownwards.sum;
    }
    if (stepUpwards.moved && stepDownwards.moved)
    {
        if (stepUpwards.distance < stepDownwards.distance)
        {
            response.moveVector = stepUpwards.sum;
        }
        else
        {
            response.moveVector = stepDownwards.sum;
        }
    }

    return response;
}
