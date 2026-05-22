#include "trajectory.hpp"

#include "core/math/line.hpp"

EntityWorldInteraction::TrajectoryCollisionResponse EntityWorldInteraction::calculateCollisionFromTrajectory(
    Vec2i start, Vec2i end, const EntityCollider &collider, const ParticleHandler &particleHandler)
{
    bool collided     = false;
    Vec2i currentPos  = start;
    Vec2i previousPos = start;

    auto check = [&](Vec2i pos)
    {
        currentPos = pos;

        Vec2i a = collider.getPrimary().getA() + pos;
        Vec2i b = collider.getPrimary().getB() + pos;

        bool collidedThisIteration = false;
        auto query                 = [&](const Particle *p)
        {
            if (p->isSolid() && !p->isMoving())
            {
                collidedThisIteration = true;
                return true;
            }

            return false;
        };
        particleHandler.query(a, b, query);

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
    response.collided        = collided;
    response.resolvePosition = previousPos;
    response.hitPosition     = currentPos;
    return response;
}

EntityWorldInteraction::TrajectoryCollisionResponse
EntityWorldInteraction::calculateCollisionFromTrajectorySlide(Vec2i start, Vec2i end,
                                                              const EntityCollider &collider,
                                                              const ParticleHandler &particleHandler)
{
    TrajectoryCollisionResponse out;

    TrajectoryCollisionResponse xy_response =
        calculateCollisionFromTrajectory(start, end, collider, particleHandler);

    // all axis
    if (xy_response.collided)
    {
        // horizontal axis
        Vec2i end_x = {end.x, xy_response.resolvePosition.y};
        TrajectoryCollisionResponse x_response =
            calculateCollisionFromTrajectory(xy_response.resolvePosition, end_x, collider, particleHandler);

        if (x_response.collided)
        {
            // vertical axis
            Vec2i end_y                            = {xy_response.resolvePosition.x, end.y};
            TrajectoryCollisionResponse y_response = calculateCollisionFromTrajectory(
                xy_response.resolvePosition, end_y, collider, particleHandler);

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
