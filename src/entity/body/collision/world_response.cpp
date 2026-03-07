#include "entity_world_collision.hpp"
#include "utils/math/line.hpp"

EntityWorldCollisionHandler::TrajectoryCollisionResponse
EntityWorldCollisionHandler::calculateCollisionFromTrajectory(Vec2<int> start,
                                                              Vec2<int> end)
{
    bool collided = false;
    Vec2<int> previousPos = start;

    auto check = [&](int x, int y)
    {
        Vec2<int> a = r_boundingBox.getA() + Vec2<int>(x, y);
        Vec2<int> b = r_boundingBox.getB() + Vec2<int>(x, y);

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
