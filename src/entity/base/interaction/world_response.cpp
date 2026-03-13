#include "entity_world_interaction.hpp"

#include "utils/math/line.hpp"

EntityWorldInteractionHandler::TrajectoryCollisionResponse
EntityWorldInteractionHandler::calculateCollisionFromTrajectory(Vec2<int> start,
                                                                Vec2<int> end)
{
    bool collided = false;
    Vec2<int> previousPos = start;

    auto check = [&](int x, int y)
    {
        Vec2<int> a = r_boundingBox.getA() + Vec2<int>(x, y);
        Vec2<int> b = r_boundingBox.getB() + Vec2<int>(x, y);

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
        r_particles.query(a, b, query);

        if (collidedThisIteration)
        {
            collided = true;
            return true;
        }

        previousPos.x = x;
        previousPos.y = y;

        return false;
    };

    Utils::Math::Line::bresenhamLine(start, end, check);

    TrajectoryCollisionResponse response;
    response.collided = collided;
    response.resolvePos = previousPos;
    return response;
}

EntityWorldInteractionHandler::TrajectoryCollisionResponse
EntityWorldInteractionHandler::calculateCollisionFromTrajectorySlide(
    Vec2<int> start, Vec2<int> end)
{
    TrajectoryCollisionResponse out;

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
                calculateCollisionFromTrajectory(xy_response.resolvePos, end_y);

            out.resolvePos = y_response.resolvePos;
        }
        else
        {
            out.resolvePos = x_response.resolvePos;
        }

        out.collided = true;
    }

    return out;
}
