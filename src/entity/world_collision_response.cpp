#include "world_collision_handler.hpp"

#include "utils/math/line.hpp"

WorldCollisionHandler::TrajectoryCollisionResponse
WorldCollisionHandler::calculateCollisionFromTrajectory(Vec2<int> start,
                                                        Vec2<int> end)
{
    bool collided = false;
    Vec2<int> previousPos = start;

    auto check = [&](int x, int y)
    {
        Vec2<int> a = m_collisionBox.getA() + Vec2<int>(x, y);
        Vec2<int> b = m_collisionBox.getB() + Vec2<int>(x, y);

        bool collidedThisIteration = false;
        auto query = [&](Particle *p)
        {
            if (p->isSolid() && !p->inMotion())
            {
                collidedThisIteration = true;
                return true;
            }

            return false;
        };
        r_world.getParticleHandler().query(a, b, query);

        if (collidedThisIteration)
        {
            // prevent floating if colliding with a single corner
            if (againstSolidCorner(Vec2<int>(previousPos.x, previousPos.y),
                                   BoundingBox::Corner::BottomLeft) &&
                !againstSolidSurface(Vec2<int>(previousPos.x, previousPos.y),
                                     BoundingBox::Side::Left) &&
                !againstSolidSurface(Vec2<int>(previousPos.x, previousPos.y),
                                     BoundingBox::Side::Bottom))
            {
                previousPos.x--;
            }
            else if (againstSolidCorner(Vec2<int>(previousPos.x, previousPos.y),
                                        BoundingBox::Corner::BottomRight) &&
                     !againstSolidSurface(
                         Vec2<int>(previousPos.x, previousPos.y),
                         BoundingBox::Side::Right) &&
                     !againstSolidSurface(
                         Vec2<int>(previousPos.x, previousPos.y),
                         BoundingBox::Side::Bottom))
            {
                previousPos.x++;
            }
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
