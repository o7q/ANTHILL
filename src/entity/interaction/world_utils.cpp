#include "math/rectangle.hpp"
#include "world_interaction.hpp"

bool WorldInteractionHandler::againstSolidSurface(Vec2i pos, RectangleSide side,
                                                  const ParticleWorld &world)
{
    Vec2u size = r_boundingBox.getSize();
    Vec2i topLeft = pos + r_boundingBox.getA();

    bool collided = false;

    auto query = [&](const Particle *p)
    {
        if (p->isSolid() && !p->isMoving())
        {
            collided = true;
            return true;
        }
        return false;
    };

    switch (side)
    {
    case RectangleSide::Top:
    {
        Vec2i start = Vec2i(topLeft.x, topLeft.y - 1);
        Vec2i end = Vec2i(topLeft.x + size.x - 1, topLeft.y - 1);
        world.query(start, end, query);
    }
    break;
    case RectangleSide::Right:
    {
        Vec2i start = Vec2i(topLeft.x + size.x, topLeft.y);
        Vec2i end = Vec2i(topLeft.x + size.x, topLeft.y + size.y - 1);
        world.query(start, end, query);
    }
    break;
    case RectangleSide::Bottom:
    {
        Vec2i start = Vec2i(topLeft.x, topLeft.y + size.y);
        Vec2i end = Vec2i(topLeft.x + size.x - 1, topLeft.y + size.y);
        world.query(start, end, query);
    }
    break;
    case RectangleSide::Left:
    {
        Vec2i start = Vec2i(topLeft.x - 1, topLeft.y);
        Vec2i end = Vec2i(topLeft.x - 1, topLeft.y + size.y - 1);
        world.query(start, end, query);
    }
    break;
    }

    return collided;
}

bool WorldInteractionHandler::againstSolidCorner(Vec2i pos,
                                                 RectangleCorner corner,
                                                 const ParticleWorld &world)
{
    Vec2i size = r_boundingBox.getSize().toInt();
    Vec2i topLeft = pos + r_boundingBox.getA();

    bool collided = false;
    switch (corner)
    {
    case RectangleCorner::TopLeft:
    {
        if (const Particle *p =
                world.getParticles().get({topLeft.x + size.x, topLeft.y - 1}))
        {
            if (p->isSolid() && !p->isMoving())
            {
                collided = true;
            }
        }
    }
    break;
    case RectangleCorner::TopRight:
    {
        if (const Particle *p =
                world.getParticles().get({topLeft.x - 1, topLeft.y - 1}))
        {
            if (p->isSolid() && !p->isMoving())
            {
                collided = true;
            }
        }
    }
    break;
    case RectangleCorner::BottomLeft:
    {
        if (const Particle *p =
                world.getParticles().get({topLeft.x - 1, topLeft.y + size.y}))
        {
            if (p->isSolid() && !p->isMoving())
            {
                collided = true;
            }
        }
    }
    break;
    case RectangleCorner::BottomRight:
    {
        if (const Particle *p = world.getParticles().get(
                {topLeft.x + size.x, topLeft.y + size.y}))
        {
            if (p->isSolid() && !p->isMoving())
            {
                collided = true;
            }
        }
    }
    break;
    }

    return collided;
}

WorldInteractionHandler::LocalWorldQuery
WorldInteractionHandler::generateLocalWorldQuery(Vec2i pos,
                                                 const ParticleWorld &world)
{
    LocalWorldQuery out;

    auto query = [&](const Particle *p)
    {
        if (p->isSolid() && !p->isMoving())
        {
            out.staticSolidCount++;
        }

        return false;
    };

    world.query(r_boundingBox.getA() + pos, r_boundingBox.getB() + pos, query);

    return out;
}
