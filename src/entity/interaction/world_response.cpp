#include "math/numbers.hpp"
#include "world_interaction.hpp"

#include "math/line.hpp"

WorldInteractionHandler::TrajectoryCollisionResponse
WorldInteractionHandler::calculateCollisionFromTrajectory(
    Vec2<int> start, Vec2<int> end, const ParticleHandler &particles)
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
        particles.query(a, b, query);

        if (collidedThisIteration)
        {
            collided = true;
            return true;
        }

        previousPos.x = x;
        previousPos.y = y;

        return false;
    };

    Math::Line::bresenhamLine(start, end, check);

    TrajectoryCollisionResponse response;
    response.collided = collided;
    response.resolvePos = previousPos;
    return response;
}

WorldInteractionHandler::TrajectoryCollisionResponse
WorldInteractionHandler::calculateCollisionFromTrajectorySlide(
    Vec2<int> start, Vec2<int> end, const ParticleHandler &particles)
{
    TrajectoryCollisionResponse out;

    TrajectoryCollisionResponse xy_response =
        calculateCollisionFromTrajectory(start, end, particles);

    // all axis
    if (xy_response.collided)
    {
        // horizontal axis
        Vec2<int> end_x = {end.x, xy_response.resolvePos.y};
        TrajectoryCollisionResponse x_response =
            calculateCollisionFromTrajectory(xy_response.resolvePos, end_x,
                                             particles);

        if (xy_response.resolvePos == x_response.resolvePos)
        {
            // vertical axis
            Vec2<int> end_y = {xy_response.resolvePos.x, end.y};
            TrajectoryCollisionResponse y_response =
                calculateCollisionFromTrajectory(xy_response.resolvePos, end_y,
                                                 particles);

            out.resolvePos = y_response.resolvePos;
        }
        else
        {
            out.resolvePos = x_response.resolvePos;
        }

        int amount = end.x - out.resolvePos.x;
        int dir = Math::Numbers::sign(amount);

        int maxStepHeight = 5;

        bool moved = false;

        int xSum = 0;
        int ySum = 0;

        for (int i = 1; i <= std::abs(amount); ++i)
        {
            int xStep = i * dir;

            Vec2<int> checkPos = {out.resolvePos.x + xStep,
                                  out.resolvePos.y - ySum};

            MTVIntersectionResponse r =
                calculateWorldIntersection_MTV(checkPos, particles);

            MTVIntersectionResponse pass2 =
                calculateWorldIntersection_MTV(checkPos + Vec2<int>(0, -r.bottom), particles);

            if (r.bottom > maxStepHeight || pass2.resolveDistance != 0)
            {
                break;
            }

            xSum = xStep;
            ySum += r.bottom;
            moved = true;
        }

        if (moved)
        {
            out.resolvePos.x += xSum;
            out.resolvePos.y -= ySum;
        }

        int aaa = end.x - out.resolvePos.x;
        if (aaa != 0)
        {
            std::cout << aaa << std::endl;
        }

        out.collided = true;
    }

    return out;
}
